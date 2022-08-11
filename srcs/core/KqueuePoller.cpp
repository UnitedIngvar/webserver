#include "KqueuePoller.hpp"

KqueuePoller::KqueuePoller(Server servers[])
{

}

KqueuePoller::~KqueuePoller()
{

}

ServerConnectionPair *KqueuePoller::pollConnections()
{
	ssize_t client_len = sizeof(client_addr);

    // Prepare the kqueue.
    _kqueue = kqueue();

    // Create event 'filter', these are the events we want to monitor.
    // Here we want to monitor: socket_listen_fd, for the events: EVFILT_READ
    // (when there is data to be read on the socket), and perform the following
    // actions on this kevent: EV_ADD and EV_ENABLE (add the event to the kqueue
    // and enable it).
    EV_SET(_changeEvent, socket_listen_fd, EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, 0);

    // Register kevent with the kqueue.
    if (kevent(_kqueue, change_event, 1, NULL, 0, NULL) == -1)
    {
        perror("kevent");
        exit(1);
    }

    // Actual event loop.
    for (;;)
    {
        // Check for new events, but do not register new events with
        // the kqueue. Hence the 2nd and 3rd arguments are NULL, 0.
        // Only handle 1 new event per iteration in the loop; 5th
        // argument is 1.
        int new_events = kevent(kq, NULL, 0, event, 1, NULL);
        if (new_events == -1)
        {
            perror("kevent");
            exit(1);
        }

        for (int i = 0; new_events > i; i++)
        {
            int event_fd = event[i].ident;

            // When the client disconnects an EOF is sent. By closing the file
            // descriptor the event is automatically removed from the kqueue.
            if (event[i].flags & EV_EOF)
            {
                printf("Client has disconnected");
                close(event_fd);
            }
            // If the new event's file descriptor is the same as the listening
            // socket's file descriptor, we are sure that a new client wants
            // to connect to our socket.
            else if (event_fd == socket_listen_fd)
            {
                // Incoming socket connection on the listening socket.
                // Create a new socket for the actual connection to client.
                socket_connection_fd = accept(event_fd, (struct sockaddr *)&client_addr, (socklen_t *)&client_len);
                if (socket_connection_fd == -1)
                {
                    perror("Accept socket error");
                }

                // Put this new socket connection also as a 'filter' event
                // to watch in kqueue, so we can now watch for events on this
                // new socket.
                EV_SET(change_event, socket_connection_fd, EVFILT_READ, EV_ADD, 0, 0, NULL);
                if (kevent(kq, change_event, 1, NULL, 0, NULL) < 0)
                {
                    perror("kevent error");
                }
            }

            else if (event[i].filter & EVFILT_READ)
            {
                // Read bytes from socket
                char buf[1024];
                size_t bytes_read = recv(event_fd, buf, sizeof(buf), 0);
                printf("read %zu bytes\n", bytes_read);
            }
        }
    }

    return 0;
}

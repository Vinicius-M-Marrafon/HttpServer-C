# HTTP SERVER IN C

## SOFTWARE USAGE

    Don't forget to CHANGE THE IPv4 ADDR!!!!! (SERVER_IPv4)

    ```console
    C:\> mingw32-make.exe httpServer
    C:\> .\httpServer.exe 
    ```

### Handle problems with winsock/HTTP request and response
    If WSACleanup is not called that can arise problems of communication!\
    [cleanup_winsock_using_netsh](https://answers.microsoft.com/en-us/microsoftedge/forum/all/errinvalidhttpresponse/c91c82f3-387a-47f0-a5cb-abb0b480085f)

    We can send the HEADER of response before sending the HTML content!
    
### Handle SIGNALs (Interruptions) 
    signal.h: [docs](https://docs.oracle.com/cd/E36784_01/html/E36873/signal.h-3head.html)\
    microsoft singal usage example: [example](https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/signal?view=msvc-170)\

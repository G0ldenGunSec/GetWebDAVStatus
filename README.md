# GetWebDAVStatus
Small project to determine if the Web Client service (WebDAV) is running on a remote system by checking for the presence of the DAV RPC SERVICE named pipe. Does not require admin privileges on the remote system, but does require some form of valid credentials (no anonymous access). Both a BOF and C# version of the project are included, the C# version is multi-threaded so would be better suited for scanning a large number of systems.

## Usage
The C# versions take a comma-seperated list of systems to scan.  The C# version also has an optional arg of "--tc" that allows the operator to control the max amount of threads to be used (default: 5). The BOF vesrion take only one argument.

BOF: `GetWebDAVStatus server01`

C#: `execute-assembly C:\assemblies\GetWebDAVStatus.exe server01,server02 --tc 1`

## Building
The C# project should be a pretty standard build, x64 + Release is the recommended build configuration.  BOF can be built with the following command from the Makefile:

`make`

## Credits
[@tifkin_](https://twitter.com/tifkin_) originally posted about this method of remotely identifying WebDAV [here](https://twitter.com/tifkin_/status/1419806476353298442).

Originally heard about the above tweet on [@flangvik](https://twitter.com/Flangvik)'s [twitch stream](https://www.twitch.tv/flangvik). Would definitely recommend checking out.

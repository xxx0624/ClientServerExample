1. should we always print GET Req into standard error? Or just when failed to send data?
2. Can I output any other error information to standard error when some bad things happen?
3. when output the header lines of response, should I output the original string? With the delimiter \r\n?
4. because this connection is one-time connection. when I extract the response body, should I do this based on the content-length information in header line or just read everything I got?
HTTP Chat Engine
===

Implement a chat server that only stores messages for 60 seconds.

Clients should be able to query for messages in ranges from `since` to `until` (in ms).

If `since` is omitted, the server should assume `since=0`

If `until` is in the past, the server should assume `until={now}` (and respond immediately).

If `until` is omitted, the server should respond the next time a message is sent to that room.

If `until` is in the future, the server should not respond until the appointed time, including all new messages in the room.

Node.JS Boilerplate:
===

    npm install -g spark

    cd ~/http-chat-nodejs
    npm install # reads in package.json for deps
    spark & # starts server.js according to config.js

Ender.JS Boilerplate:
===

    npm install -g ender

    cd ~/http-chat-nodejs/public
    ender build jeesh querystring ahr2

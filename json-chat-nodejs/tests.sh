#!/bin/bash

HOST=localhost:5080

# immediatley adds a message to RoomA
curl --silent http://${HOST}/RoomA \
  -X POST \
  -H 'Content-Type: application/json' \
  -d '{ 
          "name": "AJ"
        , "message": "Hello World"
      }'
# output should look something like
# { "error": false, "errors": [], "timestamp": 1234567890, "status": "ok"}



# immediatley adds a message to RoomB
curl --silent http://${HOST}/RoomB \
  -X POST \
  -H 'Content-Type: application/json' \
  -d '{ 
          "name": "AJ"
        , "message": "Hello Anti-World"
      }'



# waits 10 seconds before responding with the latest messages
# should get the message
let WHEN=`date +%s`000-10000 # 10 seconds ago
let THEN=`date +%s`000+10000 # 10 seconds from now
curl --silent http://${HOST}/RoomA?since=${WHEN}&until=${THEN} \
  -X POST \
  -H 'Content-Type: application/json' \
  -d '{ 
          "name": "AJ"
        , "message": "Hello Anti-World"
      }' \
  &
# output should look something like
# [
#     { "timestamp": 1234567890, "name": "AJ", "message": "blah..."}
#   , { "timestamp": 1234567890, "name": "Eric", "message": "blah..."}
# ]



# this should post to RoomA and be seen in the request above
sleep 5
curl --silent http://${HOST}/RoomA \
  -X POST \
  -H 'Content-Type: application/json' \
  -d '{ 
          "name": "Eric"
        , "message": "Hello Back Atcha"
      }'

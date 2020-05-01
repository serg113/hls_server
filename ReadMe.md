
defaullt docker ip: 192.168.99.100

service port: 7070


commands: curl 192.168.99.100:7070/frames-l-root:cm9vdDEyMzQ1NgDMzMzMzA==-l-http://192.168.99.1:8000/media/live-
command pattern: <docker_ip>:<port>/<rout_path>-l-<username>:<password_hash>-l-<stream_link>-


-- this will perform dockerfile --
download image
run container
build service 
run service

for building stream recording service

   $cd src
   $mkdir build
   $cd build
   $cmake ..
   $make

run executable



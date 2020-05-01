

1. clone repository\
2. run docker shell and cd to src/ folder

3. build docker\ 
	$docker build --tag service_test:1.0 .
	
4. $docker images\ 
	check service_test image id
	
3. docker run -it -p 7070:7070 service_test_image_id bash


for building stream recording service

   $cd src\
   $mkdir build\
   $cd build\
   $cmake ..\
   $make

run 
   $./ss
   
it will record this link http://192.168.99.1:8000/media/live

output 

test 1/2 --> saving stream as jpeg  : passed\
test 2/2 --> saving stream as video : passed


defaullt docker ip: 192.168.99.100

service port: 7070


commands: curl 192.168.99.100:7070/frames-l-root:cm9vdDEyMzQ1NgDMzMzMzA==-l-http://192.168.99.1:8000/media/live-
command pattern: <docker_ip>:<port_number>/<rout_path>-l-<user_name>:<password_hash>-l-<stream_link>-




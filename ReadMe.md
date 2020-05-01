

1. clone repository

2. run docker shell and cd to hls_server/ folder

3. build docker >>$docker build --tag service_test:1.0 .
	
4.check service_test image id  >>$docker images
	
3. >>$docker run -it -p 7070:7070 service_test_image_id bash


for building stream recording service

   $cd src\
   $mkdir build\
   $cd build\
   $cmake ..\
   $make

run 
   $./ss
   
send command by curl

defaullt docker ip: 192.168.99.100

service port: 7070

command: curl 192.168.99.100:7070/record-u:root-p:cm9vdDEyMzQ1NgDMzMzMzA==-a:http://192.168.99.1:8000/media/live-e:
command pattern: <docker_ip>:<port_number>/<rout_path>-u:<user_name>-p:<password_hash>-a<stream_link>-e:




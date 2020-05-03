

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

------------------------------------------------
iptables configuration steps for linux

1. docker run --cap-add=NET_ADMIN -it -p 7070:7070 b9dd0e28b8a4 bash
2. apt update -y\
   apt-get install iptables sudo -y

3. adduser ssuser\
   adduser ssuser sudo

4. change user\
   su - ssuser

5. check permissions\
   sudo -l


6. to accept any port from a given ip\
   sudo iptables -A INPUT -s 192.168.1.1 -j ACCEPT

7. show table\
   sudo iptables -L




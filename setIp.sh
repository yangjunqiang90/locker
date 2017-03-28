#usage : ./setIp.sh server's IP
#example : ./setIp.sh 192.168.2.125

IP=$1
sed -i "5d" locker/locker/main.cpp 
sed -i "4a QString ip=\"$IP\";" locker/locker/main.cpp

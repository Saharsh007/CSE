## two routers and 3 nodes attached to both of them l1,l2,l3 on left and r1,r2,r3 on right. ping l2 to r2. 
## 100mbps bandwidth 5ms latency between access links 
## 10mbps and 40ms for bottleneck
## run 5 tcp streams  and measure the ping

# set -eE -o functrace

# failure() {
#   local lineno=$1
#   local msg=$2
#   echo "Failed at $lineno: $msg"
# }
# trap 'failure ${LINENO} "$BASH_COMMAND"' ERR

#delete all
sudo ip netns del l1
sudo ip netns del l2
sudo ip netns del l3
sudo ip netns del r1
sudo ip netns del r2
sudo ip netns del r3
sudo ip netns del b1
sudo ip netns del b2
printf "deleted all namespaces to start fresh\n"

# create the namespaces
sudo ip netns add l1
sudo ip netns add l2
sudo ip netns add l3

sudo ip netns add r1
sudo ip netns add r2
sudo ip netns add r3

sudo ip netns add b1
sudo ip netns add b2
printf "namespaces created \n"

# create 7 veth pairs
sudo ip link add l1b1 type veth peer name b1l1
sudo ip link add l2b1 type veth peer name b1l2
sudo ip link add l3b1 type veth peer name b1l3

sudo ip link add r1b2 type veth peer name b2r1
sudo ip link add r2b2 type veth peer name b2r2
sudo ip link add r3b2 type veth peer name b2r3

sudo ip link add b1b2 type veth peer name b2b1
printf "creating veth pairs successful\n"

# Set the veth interfaces inside the namespaces
sudo ip link set l1b1 netns l1
sudo ip link set l2b1 netns l2
sudo ip link set l3b1 netns l3

sudo ip link set r1b2 netns r1
sudo ip link set r2b2 netns r2
sudo ip link set r3b2 netns r3

sudo ip link set b1l1 netns b1
sudo ip link set b1l2 netns b1
sudo ip link set b1l3 netns b1   

sudo ip link set b2r1 netns b2
sudo ip link set b2r2 netns b2
sudo ip link set b2r3 netns b2

sudo ip link set b1b2 netns b1
sudo ip link set b2b1 netns b2
printf "connecting veth pair with namespaces\n"

# Bring up the interfaces within namespaces
sudo ip netns exec l1 ip link set l1b1 up
sudo ip netns exec l2 ip link set l2b1 up
sudo ip netns exec l3 ip link set l3b1 up
sudo ip netns exec b1 ip link set b1l1 up
sudo ip netns exec b1 ip link set b1l2 up
sudo ip netns exec b1 ip link set b1l3 up

sudo ip netns exec r1 ip link set r1b2 up
sudo ip netns exec r2 ip link set r2b2 up
sudo ip netns exec r3 ip link set r3b2 up
sudo ip netns exec b2 ip link set b2r1 up
sudo ip netns exec b2 ip link set b2r2 up
sudo ip netns exec b2 ip link set b2r3 up


sudo ip netns exec b1 ip link set b1b2 up
sudo ip netns exec b2 ip link set b2b1 up

printf "bring up the interfaces withine namespaces\n"


# Assign interfaces within namespaces IP addresses
sudo ip netns exec l1 ip address add 10.0.1.1/24 dev l1b1
sudo ip netns exec l2 ip address add 10.0.2.1/24 dev l2b1
sudo ip netns exec l3 ip address add 10.0.3.1/24 dev l3b1

sudo ip netns exec b1 ip address add 10.0.1.2/24 dev b1l1
sudo ip netns exec b1 ip address add 10.0.2.2/24 dev b1l2
sudo ip netns exec b1 ip address add 10.0.3.2/24 dev b1l3

sudo ip netns exec r1 ip address add 10.0.4.1/24 dev r1b2
sudo ip netns exec r2 ip address add 10.0.5.1/24 dev r2b2
sudo ip netns exec r3 ip address add 10.0.6.1/24 dev r3b2

sudo ip netns exec b2 ip address add 10.0.4.2/24 dev b2r1
sudo ip netns exec b2 ip address add 10.0.5.2/24 dev b2r2
sudo ip netns exec b2 ip address add 10.0.6.2/24 dev b2r3

sudo ip netns exec b1 ip address add 10.0.7.1/24 dev b1b2
sudo ip netns exec b2 ip address add 10.0.7.2/24 dev b2b1


printf "IP address assigned\n"


# Add default gateway, i.e. it serves as a forwarding host to connect to other networks
sudo ip netns exec l1 ip route add default via 10.0.1.2 dev l1b1
sudo ip netns exec l2 ip route add default via 10.0.2.2 dev l2b1
sudo ip netns exec l3 ip route add default via 10.0.3.2 dev l3b1

sudo ip netns exec r1 ip route add default via 10.0.4.2 dev r1b2
sudo ip netns exec r2 ip route add default via 10.0.5.2 dev r2b2
sudo ip netns exec r3 ip route add default via 10.0.6.2 dev r3b2

sudo ip netns exec b1 ip route add default via 10.0.7.2 dev b1b2
sudo ip netns exec b2 ip route add default via 10.0.7.1 dev b2b1


printf "Gateway assigned\n"


# Enable IP forwarding : Make a system to act as a router i.e., it should determine the path a packet has to take to reach it’s destination
sudo ip netns exec b1 sysctl -w net.ipv4.ip_forward=1
sudo ip netns exec b2 sysctl -w net.ipv4.ip_forward=1


# Try ping now,
sudo ip netns exec l1 ping 10.0.4.1 -c 2
sudo ip netns exec l1 ping 10.0.5.1 -c 2
sudo ip netns exec r1 ping 10.0.3.1 -c 2

echo "\n\n                     changing bandwidth and latency\n\n"

echo "intial speed"
sleep 5s

sudo ip netns exec l1 iperf -c 10.0.4.1



# changing bandwidth values

sudo ip netns exec l1 tc qdisc add dev l1b1 root tbf rate 100mbit burst 100kbit latency 5ms
sudo ip netns exec l2 tc qdisc add dev l2b1 root tbf rate 100mbit burst 100kbit latency 5ms
sudo ip netns exec l3 tc qdisc add dev l3b1 root tbf rate 100mbit burst 100kbit latency 5ms

sudo ip netns exec r1 tc qdisc add dev r1b2 root tbf rate 100mbit burst 100kbit latency 5ms
sudo ip netns exec r2 tc qdisc add dev r2b2 root tbf rate 100mbit burst 100kbit latency 5ms
sudo ip netns exec r3 tc qdisc add dev r3b2 root tbf rate 100mbit burst 100kbit latency 5ms

sudo ip netns exec b1 tc qdisc add dev b1b2 root tbf rate 10mbit burst 100kbit latency 40ms

echo "\nfinal speed"
sleep 5s

sudo ip netns exec l1 iperf -c 10.0.4.1  -i 1 -P 5



# Try ping now,
sudo ip netns exec l1 ping 10.0.4.1 -c 2
sudo ip netns exec l1 ping 10.0.5.1 -c 2
sudo ip netns exec r1 ping 10.0.3.1 -c 2





# 3 routers. Two connectedt to the middle one
# 3 nodes , each connected to one router.

set -eE -o functrace

failure() {
  local lineno=$1
  local msg=$2
  echo "Failed at $lineno: $msg"
}
trap 'failure ${LINENO} "$BASH_COMMAND"' ERR

#delete node
sudo ip netns del l1
sudo ip netns del m1
sudo ip netns del r1
sudo ip netns del b1
sudo ip netns del b2
sudo ip netns del b3
echo "deleted all the network namespaces\n"

# add node
sudo ip netns add l1
sudo ip netns add r1
sudo ip netns add m1
sudo ip netns add b1
sudo ip netns add b2
sudo ip netns add b3

echo "created all the namespaces\n"

# add veth pairs
sudo ip link add l1b1 type veth peer name b1l1
sudo ip link add m1b2 type veth peer name b2m1
sudo ip link add r1b3 type veth peer name b3r1
sudo ip link add b1b2 type veth peer name b2b1
sudo ip link add b2b3 type veth peer name b3b2

echo "veth pairs created\n"

# connect namespace with veth pair

sudo ip link set l1b1 netns l1
sudo ip link set m1b2 netns m1
sudo ip link set r1b3 netns r1

sudo ip link set b1b2 netns b1
sudo ip link set b2b3 netns b2

sudo ip link set b1l1 netns b1
sudo ip link set b2m1 netns b2
sudo ip link set b3r1 netns b3

sudo ip link set b2b1 netns b2
sudo ip link set b3b2 netns b3

echo "connected veth with namespaces successfully"

# assign ip address to veth pair ends connected with namespaces

sudo ip netns exec l1 ip address add 10.0.1.1/24 dev l1b1 
sudo ip netns exec m1 ip address add 10.0.2.1/24 dev m1b2
sudo ip netns exec r1 ip address add 10.0.3.1/24 dev r1b3

sudo ip netns exec b1 ip address add 10.0.4.1/24 dev b1b2
sudo ip netns exec b2 ip address add 10.0.5.1/24 dev b2b3

sudo ip netns exec b1 ip address add 10.0.1.2/24 dev b1l1
sudo ip netns exec b2 ip address add 10.0.2.2/24 dev b2m1
sudo ip netns exec b3 ip address add 10.0.3.2/24 dev b3r1

sudo ip netns exec b2 ip address add 10.0.4.2/24 dev b2b1
sudo ip netns exec b3 ip address add 10.0.5.2/24 dev b3b2

echo "ip addresses assigned\n"

# up the namespaces
sudo ip netns exec l1 ip link set l1b1 up
sudo ip netns exec m1 ip link set m1b2 up
sudo ip netns exec r1 ip link set r1b3 up

sudo ip netns exec b1 ip link set b1l1 up
sudo ip netns exec b2 ip link set b2m1 up
sudo ip netns exec b3 ip link set b3r1 up

sudo ip netns exec b1 ip link set b1b2 up
sudo ip netns exec b2 ip link set b2b3 up
sudo ip netns exec b2 ip link set b2b1 up
sudo ip netns exec b3 ip link set b3b2 up

echo "namespaces up\n"

# loopbackup
sudo ip netns exec l1 ip link set lo up
sudo ip netns exec m1 ip link set lo up
sudo ip netns exec r1 ip link set lo up
sudo ip netns exec b1 ip link set lo up
sudo ip netns exec b2 ip link set lo up
sudo ip netns exec b3 ip link set lo up


# add default gateway
sudo ip netns exec l1 ip route add default via 10.0.1.2 dev l1b1
sudo ip netns exec m1 ip route add default via 10.0.2.2 dev m1b2
sudo ip netns exec r1 ip route add default via 10.0.3.2 dev r1b3
# sudo ip netns exec b1 ip route add default via 10.0.4.2 dev b1b2
# sudo ip netns exec b2 ip route add default via 10.0.5.2 dev b2b3
# sudo ip netns exec b2 ip route add default via 10.0.4.1 dev b2b1
# sudo ip netns exec b3 ip route add default via 10.0.5.1 dev b3b2

printf "Gateway assigned\n"

# configuring the routers
sudo ip netns exec b1 sysctl -w net.ipv4.ip_forward=1
sudo ip netns exec b2 sysctl -w net.ipv4.ip_forward=1
sudo ip netns exec b3 sysctl -w net.ipv4.ip_forward=1

echo "routers configured"

# Try ping now
sudo ip netns exec l1 ping 10.0.4.2 -c 5
sudo ip netns exec l1 ping 10.0.3.1 -c 5
sudo ip netns exec m1 ping 10.0.3.1 -c 5
sudo ip netns exec r1 ping 10.0.1.1 -c 5

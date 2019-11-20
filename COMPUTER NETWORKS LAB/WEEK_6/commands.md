## Ping a network namespace from the default namespace.
    // create namespace  
    sudo ip netns add red

    // Bring loopback interfaces up
    sudo ip netns exec red ip link set lo up

    //ping ip address
    sudo ip netns exec red ping 127.0.0.1


## Ping a network namespace from another network namespace.

    // create namespace
    sudo ip netns add red
    sudo ip netns add blue

    // Create veth pairs
    sudo ip link add veth-red type veth peer name veth-blue

    // Set the veth interfaces inside the namespaces
    sudo ip link set veth-red netns red
    sudo ip link set veth-blue netns blue

    // Assign interfaces within namespaces IP addresses
    sudo ip netns red ip address add 10.0.0.1/24 dev veth-red
    sudo ip netns blue ip address add 10.0.0.3/24 dev veth-blue

    // bring up the interfaces
    sudo ip -n red link set veth-red up
    sudo ip -n blue link set veth-blue up

    // Now ping, it works
    sudo ip netns exec red ping 10.0.0.2  

## Ping a network namespace from another network namespace via linux bridge

    // create namespace
    sudo ip netns add red
    sudo ip netns add blue

    // Create veth pairs
    sudo ip link add eth0 type veth peer name eth1
    sudo ip link add eth2 type veth peer name eth3

    // Set the veth interfaces inside the namespaces
    sudo ip link set eth0 netns red
    sudo ip link set eth2 netns blue

    // Bring up the interfaces within namespaces
    // loopback is used to ping self
    sudo ip netns exec red ip link set eth0 up
    sudo ip netns exec blue ip link set eth2 up

    // Bring up the interfaces within namespaces
    sudo ip netns exec red ip link set eth0 up
    sudo ip netns exec blue ip link set eth2 up

    // Assign interfaces within namespaces IP addresses
    sudo ip netns exec red ip address add 10.0.0.1/24 dev eth0
    sudo ip netns exec blue ip address add 10.0.0.3/24 dev eth2

    // Create bridge using iproute package. Brctl is deprecated
    sudo ip link add name br0 type bridge
    sudo ip link set dev br0 up

    // Set the other lose interfaces into the bridge
    sudo ip link set eth1 master br0
    sudo ip link set eth3 master br0

    //Bring bridge interfaces up
    sudo ip link set dev eth1 up
    sudo ip link set dev eth3 up

    // Now ping, it works
    sudo ip netns exec red ping 10.0.0.3
    sudo ip netns exec blue ping 10.0.0.1


## Ping a network namespace from another network namespace via a third network namespace.

    // Create two namespaces
    sudo ip netns add red
    sudo ip netns add green

    // Create three veth pairs
    sudo ip link add eth0 type veth peer name eth1
    sudo ip link add eth2 type veth peer name eth3

    // Set them into the namespaces
    sudo ip link set eth0 netns red
    sudo ip link set eth2 netns green

    // Bring them up
    sudo ip netns exec red ip link set eth0 up
    sudo ip netns exec green ip link set eth2 up

    // Assign IP address to them (all different subnets)
    sudo ip netns exec red ip address add 10.0.0.1/24 dev eth0
    sudo ip netns exec green ip address add 10.0.2.1/24 dev eth2

    // Create router namespace and add appropriate interfaces into it
    sudo ip netns add router
    sudo ip link set eth1 netns router
    sudo ip link set eth3 netns router

    // Bring the interface up
    sudo ip netns exec router ip link set eth1 up
    sudo ip netns exec router ip link set eth3 up

    // Assign IP addresses to the interfaces within router
    sudo ip netns exec router ip address add 10.0.0.2/24 dev eth1
    sudo ip netns exec router ip address add 10.0.2.2/24 dev eth3

    // Add default gateway, i.e. it serves as a forwarding host to connect to other networks
    sudo ip netns exec red ip route add default via 10.0.0.2 dev eth0
    sudo ip netns exec green ip route add default via 10.0.2.2 dev eth2

    //Enable IP forwarding : Make a system to act as a router i.e., it should determine the path a packet has to take to reach it’s destination 
    sudo ip netns exec router sysctl -w net.ipv4.ip_forward=1

    // Try ping now, it works
    sudo ip netns exec red ping 10.0.2.1


## two routers and 3 nodes attached to both of them l1,l2,l3 on left and r1,r2,r3 on right. ping l2 to r2. 
## 100mbps bandwidth 5ms latency between access links 
## 10mbps and 40ms for bottleneck
## run 5 tcp streams  and measure the ping


    // create the namespaces
    sudo ip netns l1
    sudo ip netns l2
    sudo ip netns l3

    sudo ip netns r1
    sudo ip netns r2
    sudo ip netns r3
    
    sudo ip netns b1
    sudo ip netns b2

    // create 7 veth pairs
    sudo ip link add l1b1 type veth peer name b1l1
    sudo ip link add l2b1 type veth peer name b1l2
    sudo ip link add l3b1 type veth peer name b1l3
    
    sudo ip link add r1b2 type veth peer name b2r1
    sudo ip link add r2b2 type veth peer name b2r2
    sudo ip link add r3b2 type veth peer name b2r3
    
    sudo ip link add b1b2 type veth peer name b2b1

    // Set the veth interfaces inside the namespaces
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

    // Bring up the interfaces within namespaces
    sudo ip netns exec l1 ip link set l1b1 up
    sudo ip netns exec l2 ip link set l2b1 up
    sudo ip netns exec l3 ip link set l3b1 up
    sudo ip netns exec b1 ip link set b1l1 up
    sudo ip netns exec b1 ip link set b1l2 up
    sudo ip netns exec b1 ip link set b1l3 up

    sudo ip netns exec r1 ip link set l1b1 up
    sudo ip netns exec r2 ip link set l1b1 up
    sudo ip netns exec r3 ip link set l1b1 up
    sudo ip netns exec b2 ip link set b2r1 up
    sudo ip netns exec b2 ip link set b2r2 up
    sudo ip netns exec b2 ip link set b2r3 up


    sudo ip netns exec b1 ip link set l1b1 up
    sudo ip netns exec b2 ip link set l1b1 up

    // Assign interfaces within namespaces IP addresses
    sudo ip netns exec l1 address add 10.0.1.1 dev l1b1
    sudo ip netns exec l2 address add 10.0.2.1 dev l2b1
    sudo ip netns exec l3 address add 10.0.3.1 dev l3b1

    sudo ip netns exec b1 address add 10.0.1.2 dev l1b1    





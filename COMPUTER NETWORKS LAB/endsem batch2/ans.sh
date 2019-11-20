## two routers and 3 nodes attached to both of them l1,l2,l3 on left and r1,r2,r3 on right. ping l2 to r2. 
## 100mbps bandwidth 5ms latency between access links 
## 10mbps and 40ms for bottleneck
## run 5 tcp streams  and measure the ping


    # create the namespaces
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






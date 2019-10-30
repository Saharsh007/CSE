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
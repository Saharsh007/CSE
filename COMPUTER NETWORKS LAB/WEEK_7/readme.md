##  What is the difference between a hub, a switch and a router?
- Hub - message recieved by hub is sent to all the other systems connected by it and the systems decide if they want to keep the message or not.   
HUB IS ON PHYSICAL LAYER
- Switch - A switch is able to handle the data and knows the specific addresses to send the message. It can decide which computer is the message intended for and send the message directly to the right computer.   
SWITCH IS ON DATALINK LAYER. 
- Router - Router is actually a small computer that can be programmed to handle and route the network traffic. It usually connects at least two networks together, such as two LANs, two WANs or a LAN and its ISP network. Routers can calculate the best route for sending data and communicate with each other by protocols.  
- Also it buffers packets and sends to client in case of overflow 
ROUTERS ARE ON NETWORK LAYER.

## What is a Linux Bridge
- Virtual bridge
- Link Layer device which forwards traffic between networks based on MAC addresses and is therefore also referred to as a Layer 2 device.
- It makes forwarding decisions based on tables of MAC addresses which it builds by learning what hosts are connected to each network.


## Open vSwitch
- distributed virtual multilayer switch.
- connects two devices.

## veth interface
- its like cable of real world
- connects two namespaces

## routing table
- it is used by router to find which is the destination for a specfic packet and  which is the shortest path
- print routing table in linux - "netstat -rn"
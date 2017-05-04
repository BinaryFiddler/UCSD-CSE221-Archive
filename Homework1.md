# CSE221 Operating System, Homework 1

* Student Name: Chenyu Huang
* PID: A53202846
* Email: [chh217@eng.ucsd.edu](chh217@eng.ucsd.edu)

## Question 1:

### Hydra

##### Protection Domain

A protection domain in Hydra is the "Local name space" (LNS). An LNS represents the current set of objects and rights to which a process has access, and those objects and rights change when a process moves from one LNS to another. 

##### Crossing protection domain borders



##### Rights representation

Hydra represents rights in terms of 'capability'. A capability consists of a reference to an object together with a collection of access rights to that object. In Hydra, capabilities are only manipulated by the kernel. 

##### Right amplication

##### Protection domain border crossing decision process



### UNIX

##### Protection Domain



### Multics



### Pilot

##### Protection Domain



## Question 2

Example

In Multics, most of the burden of keeping users' programs from interfering with one another, with protected subsystems, and with the supervisor is carried by a second level of mechanism (first level being access control list), which is descriptor-based. This second level is implemented mostly in hardware in the central processing unit of the Honeywell 6180.

Advantage

Calls to protected subsystems use the same structural mechanisms as do calls to unprotected subroutines, with the same cost in execution time. This means that a programer does not need to take the fact that he is calling a protected subsystem into account when he tries to estimate the performance of a new program design. 

Drawback

The biggest drawback of using specialized hardware is that it impedes system availability on different hardware architectures. If a system replies on a specific piece of hardware to facilitate its implementation, it is unlikely it will run on machines without that hardware. The tight coupling of hardware and OS also indicates that changes made to the OS sometimes would require corresponding changes to the hardware. This could mean replacing hardware parts or even the entire machine in order to perform OS update. 

Today

Today, specialized hardware are still used to facilitate some system implementations. For instance, the implementation of virtual memory almost always require some forms of hardware support, typically in the form of a memory management unit in the CPU (which translates virtual addresses to physical addresses). 

## Question 3

First of all, being a multi-user timesharing systems like UNIX doesn't neccessarily means that it is not suitable for personal computers. However, a single user system like Pilot will render utterly useless for a multi-user environment. Besides, UNIX is designed to be portable, it is not tightly coupled with any hardware, meaning that it can run on almost any hardware without major overhaul. Additionally, modern systems that based on 'old warhorse' systems like UNIX have evolved a with the addition of new features such as networking which makes them suitable for modern use. 
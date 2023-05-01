Group Names: 
    Charlie Miller
    Vamsi Lakshman Varma Datla
    Anthony Horinek
    Jonathan Griffith
    Douglas Edmondson

Date: 12/05/2022

Problem description:
Consider a jewelry shop has employed Na number of shop assistants to handle Nc (typically much larger than Na) number of customers. One shop assistant can only handle one customer at any time. The shop has arranged Ns (typically much smaller than Nc) number of sofas in the waiting room so that when all the shop assistants are busy helping the customers, the customers can sit. Only one customer can occupy one sofa at any time. The customers will sit on the sofa only if the sofa is not occupied. If all the sofas are occupied, then the customer will stand. If there is any sofa left, then no customer will be standing. Nmax is the limit on the maximum number of customers that can be in the waiting room at any time. If the number of customers in the waiting room exceeds this limit, then no new customer is allowed in the shop.
When the customer is done shopping, he/she can leave the shop. The shop assistant then brings the customer from the waiting room. The customer who has been waiting for the longest period (i.e., sitting on the sofa for the longest period) will be the next to get assistance. The customer in the waiting room can also decide to leave without doing any shopping.
When the customer gets the shop assistant, only then will the customer be able to do the shopping. Shopping can mean any of the following activities:
1. Looking at the jewelry menu
2. Making specific jewelry inquiry
3. Making purchase
4. Returning the purchase
5. Exit

I was responsible for creating the server for the rest of the group's code to run off, and client terminals to connect with. Code initialzes the shared memory for the assistants, inventory, and message queue, calls the requested amount of handlers for the assistants, opens the server socket, and waits for connections.

Note this is an incomplete project as other member's code will not be uploaded.

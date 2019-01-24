//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#include "Node.h"


Define_Module(Node);

void Node::initialize()
{
    address=par("address");
    in=gate("gIn");
    out=gate("gOut");

    counter = 1;
    counter1=1;

    if(address==1){
        cMessage* event=new cMessage();
        scheduleAt(0,event);
    }

    // TODO - Generated method body
}

void Node::handleMessage(cMessage *msg)
{
    if(msg->isSelfMessage())
    {
        N_PDU* data=new N_PDU();
        data->setPId(counter);
        data ->setType(1);
        send(data,out);
        counter++;
    }
    else{
               if(counter<=10)
               {
                   N_PDU *ap=check_and_cast<N_PDU*>(msg);
                   if(ap->getType()==0)
                   {
                       N_PDU* data=new N_PDU();
                       data->setPId(counter);
                       data ->setType(1);
                       send(data,out);
                       counter++;
                   }
                   else{

                       N_PDU* Ack = new N_PDU();
                       Ack->setPId(counter1);
                       Ack ->setType(0);
                       send(Ack,out);
                       counter1++;
                   }
               }

    }
}

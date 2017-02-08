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

#include "application_l.h"


Define_Module(Application_l);

void Application_l::initialize()
{
    id = par("id");
    counter = 0;
    numSent = 0;
    numReceived = 0;

    if (id == 1) {
        A_PDU *msg = new A_PDU();
        msg->setPkt_id(counter);
        msg->setMsg(counter);
        msg->setMsg_type("Data");
        msg->setSource_id(1);
        msg->setDestination_id(2);
        numSent++;
        send(msg, "out");
    }
}

void Application_l::handleMessage(cMessage *msg)
{
    A_PDU *msg_old = check_and_cast<A_PDU*> (msg);

    int hopcount = msg_old->getHop_count();
    hopCountVector.record(hopcount);
    hopCountStats.collect(hopcount);

    if(id == 2){
        numReceived++;
        A_PDU *msg_new = new A_PDU();
        msg_new->setHop_count(hopcount+1);
        msg_new->setPkt_id(msg_old->getPkt_id());
        msg_new->setMsg(msg_old->getMsg());
        msg_new->setMsg_type("Ack");
        msg_new->setSource_id(2);
        msg_new->setDestination_id(1);

        numSent++;
        send(msg_new, "out");
    } else if(id == 1 && counter < 25){
        numReceived++;
        A_PDU *msg_new = new A_PDU();
        counter++;
        msg_new->setHop_count(hopcount+1);
        msg_new->setPkt_id(counter);
        msg_new->setMsg(counter + 'A');
        msg_new->setMsg_type("Data");
        msg_new->setSource_id(1);
        msg_new->setDestination_id(2);

        numSent++;
        send(msg_new, "out");
    }
    delete msg_old;
}

void Application_l::refreshDisplay() const
{
    char buf[40];
    sprintf(buf, "rcvd: %ld sent: %ld", numReceived, numSent);
    getDisplayString().setTagArg("t", 0, buf);
}

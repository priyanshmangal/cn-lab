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
#include "a_pdu_m.h"
#include "dl_pdu_m.h"

Define_Module(Application_l);

void Application_l::initialize()
{
    id = par("id");

    if (id == 1) {
        A_PDU *msg = new A_PDU();
        msg->setPkt_id(1);
        msg->setMsg_type("Data");
        msg->setSource_id(1);
        msg->setDestination_id(2);
        send(msg, "out");
    }
}

void Application_l::handleMessage(cMessage *msg)
{
    A_PDU *msg_old = check_and_cast<A_PDU*> (msg);

    if(id == 2 && msg_old->getPkt_id() <= 10){
        A_PDU *msg_new = new A_PDU();
        msg_new->setPkt_id(msg_old->getPkt_id());
        msg_new->setMsg_type("Ack");
        msg_new->setSource_id(2);
        msg_new->setDestination_id(1);

        send(msg_new, "out");
    } else if(id == 1 && msg_old->getPkt_id() < 10){
        A_PDU *msg_new = new A_PDU();
        msg_new->setPkt_id(msg_old->getPkt_id() + 1);
        msg_new->setMsg_type("Data");
        msg_new->setSource_id(1);
        msg_new->setDestination_id(2);

        send(msg_new, "out");
    }
    delete msg_old;
}

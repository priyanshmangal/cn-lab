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

#include "datalink_l.h"
#include "a_pdu_m.h"
#include "dl_pdu_m.h"
#include "p_pdu_m.h"

Define_Module(Datalink_l);

void Datalink_l::initialize()
{
    id = par("id");
    in_a = gate("in_a");
    out_a = gate("out_a");
    in_p = gate("in_p");
    out_p = gate("out_p");
}

void Datalink_l::handleMessage(cMessage *msg)
{
    if(msg->getArrivalGate() == in_a){
        A_PDU *msg_old = check_and_cast<A_PDU*> (msg);
        DL_PDU *msg_new = new DL_PDU();

        msg_new->encapsulate(msg_old);
        msg_new->setPkt_id_dl(msg_old->getPkt_id()%2);
        send(msg_new, "out_p");
    } else if(msg->getArrivalGate() == in_p){
        DL_PDU *msg_old = check_and_cast<DL_PDU*> (msg);
        A_PDU *msg_new = new A_PDU();

        msg_new = check_and_cast<A_PDU*> (msg_old->decapsulate());
        send(msg_new, "out_a");
        delete msg_old;
    }
}

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

#include "physical_l.h"


Define_Module(Physical_l);

void Physical_l::initialize()
{
    numSent = 0;
    numReceived = 0;

    id = par("id");
    in_n = gate("in_n");
    out_n = gate("out_n");
    in_d = gate("in_d");
    out_d = gate("out_d");
}

void Physical_l::handleMessage(cMessage *msg)
{
    if(msg->getArrivalGate() == in_d){
        numReceived++;
        DL_PDU *msg_old = check_and_cast<DL_PDU*> (msg);
        P_PDU *msg_new = new P_PDU();

        msg_new->encapsulate(msg_old);
        send(msg_new, "out_n");
        numSent++;
    } else  if(msg->getArrivalGate() == in_n){
        numReceived++;
        if (uniform(0, 1) < 0.1 && id == 1) {
            EV << "\"Losing\" message\n";
            delete msg;
        } else if (uniform(0, 1) < 0.15 && id == 2) {
            EV << "\"Losing\" message\n";
            delete msg;
        } else {
            P_PDU *msg_old = check_and_cast<P_PDU*> (msg);
            DL_PDU *msg_new = new DL_PDU();

            msg_new = check_and_cast<DL_PDU*> (msg_old->decapsulate());
            send(msg_new, "out_d");
            numSent++;
            delete msg_old;
        }
    }
}

void Physical_l::refreshDisplay() const
{
    char buf[40];
    sprintf(buf, "rcvd: %ld sent: %ld", numReceived, numSent);
    getDisplayString().setTagArg("t", 0, buf);
}

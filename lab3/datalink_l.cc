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

Define_Module(Datalink_l);

void Datalink_l::initialize()
{
    timeoutEvent = new cMessage("timeoutEvent");
    timeout = 5.0;
    timeoutMsg = nullptr;

    delayEvent = new cMessage("delayEvent");
    delayMsg = nullptr;

    numSent = 0;
    numReceived = 0;

    id = par("id");
    in_a = gate("in_a");
    out_a = gate("out_a");
    in_p = gate("in_p");
    out_p = gate("out_p");
}

void Datalink_l::handleMessage(cMessage *msg)
{
    if (msg == timeoutEvent) {
       EV << "Timeout expired, resending message and restarting timer\n";
       send(timeoutMsg, "out_p");
       numSent++;
       scheduleAt(simTime()+timeout, timeoutEvent);
   } else if (msg == delayEvent) {
       A_PDU *msg_new = check_and_cast<A_PDU*> (delayMsg->decapsulate());
       send(msg_new, "out_a");
       numSent++;
       delayMsg = nullptr;
   } else if(msg->getArrivalGate() == in_a && id == 1){
        numReceived++;
        A_PDU *msg_old = check_and_cast<A_PDU*> (msg);
        DL_PDU *msg_new = new DL_PDU();

        msg_new->encapsulate(msg_old);
        msg_new->setPkt_id_dl(msg_old->getPkt_id()%2);
        timeoutMsg = msg_new->dup();;

        send(msg_new, "out_p");
        numSent++;
        scheduleAt(simTime()+timeout, timeoutEvent);
    } else if(msg->getArrivalGate() == in_p && id == 1){
        numReceived++;
        delayMsg = check_and_cast<DL_PDU*> (msg);
        cancelEvent(timeoutEvent);

        if (uniform(0, 1) < 0.3) {
            scheduleAt(simTime()+2.0, delayEvent);
        } else {
            scheduleAt(simTime()+1.0, delayEvent);
        }
    } else if(msg->getArrivalGate() == in_a && id == 2){
        numReceived++;
        A_PDU *msg_old = check_and_cast<A_PDU*> (msg);
        DL_PDU *msg_new = new DL_PDU();

        msg_new->encapsulate(msg_old);
        msg_new->setPkt_id_dl(msg_old->getPkt_id()%2);
        send(msg_new, "out_p");
        numSent++;
    } else if(msg->getArrivalGate() == in_p && id == 2){
        numReceived++;
        delayMsg = check_and_cast<DL_PDU*> (msg);

        if (uniform(0, 1) < 0.4) {
            scheduleAt(simTime()+2.0, delayEvent);
        } else {
            scheduleAt(simTime()+1.0, delayEvent);
        }
    }
}

void Datalink_l::refreshDisplay() const
{
    char buf[40];
    sprintf(buf, "rcvd: %ld sent: %ld", numReceived, numSent);
    getDisplayString().setTagArg("t", 0, buf);
}

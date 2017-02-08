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

#ifndef __LAB2_DATALINK_L_H_
#define __LAB2_DATALINK_L_H_

#include <omnetpp.h>
#include "a_pdu_m.h"
#include "dl_pdu_m.h"

using namespace omnetpp;

/**
 * TODO - Generated class
 */
class Datalink_l : public cSimpleModule
{
  private:
    simtime_t timeout;
    cMessage *timeoutEvent;

    cMessage *delayEvent;

    long numSent;
    long numReceived;
  protected:
    int id;
    cGate* in_a;
    cGate* out_a;
    cGate* in_p;
    cGate* out_p;
    DL_PDU *delayMsg;
    cMessage *timeoutMsg;

    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual void refreshDisplay() const override;
};

#endif

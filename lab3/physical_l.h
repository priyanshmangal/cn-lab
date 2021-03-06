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

#ifndef __LAB2_PHYSICAL_L_H_
#define __LAB2_PHYSICAL_L_H_

#include <omnetpp.h>
#include "dl_pdu_m.h"
#include "p_pdu_m.h"

using namespace omnetpp;

/**
 * TODO - Generated class
 */
class Physical_l : public cSimpleModule
{
  private:
    long numSent;
    long numReceived;
    cLongHistogram hopCountStats;
    cOutVector hopCountVector;
  protected:
    int id;
    cGate* in_n;
    cGate* out_n;
    cGate* in_d;
    cGate* out_d;
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual void refreshDisplay() const override;
};

#endif

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

package lab3;

module Node
{
    parameters:
        int Nid;
        @display("bgb=574,592");
    gates:
        input in;
        output out;
    submodules:
        datalink_l: Datalink_l {
            id = Nid;
            @display("p=275,308");
        }
        application_l: Application_l {
            id = Nid;
            @display("p=63,521");
        }
        physical_l: Physical_l {
            id = Nid;
            @display("p=452,111");
        }
    connections:
        datalink_l.out_a --> application_l.in;
        datalink_l.in_a <-- application_l.out;

        datalink_l.out_p --> physical_l.in_d;
        datalink_l.in_p <-- physical_l.out_d;

        out <-- physical_l.out_n;
        in --> physical_l.in_n;

}

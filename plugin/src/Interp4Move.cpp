#include <iostream>
#include "Interp4Move.hh"
#include "MobileObj.hh"

using std::cout;
using std::endl;


extern "C" {
 Interp4Command* CreateCmd(void);
  const char* GetCmdName() { return "Move"; }
}




/*!
 * \brief
 *
 *
 */
Interp4Command* CreateCmd(void)
{
  return Interp4Move::CreateCmd();
}


/*!
 *
 */
Interp4Move::Interp4Move(): speed(0), trip_length(0)
{}


/*!
 *
 */
void Interp4Move::PrintCmd() const
{
  cout << GetCmdName() << " Obj_A " << " " << speed << " " << trip_length << " " << endl;
}


/*!
 *
 */
const char* Interp4Move::GetCmdName() const
{
  return ::GetCmdName();
}


/*!
 *
 */
bool Interp4Move::ExecCmd( MobileObj  *pMobObj,  AccessControl *pAccCtrl) const
{
  int direction = this->speed > 0 ? 1 : -1;
  int iterations = std::floor(this->trip_length/this->speed);

  for (int i = 0; i < iterations; ++i)
  {
    pAccCtrl->LockAccess();

    Vector3D position = pMobObj->GetPositoin_m();
    double angle = pMobObj->GetAng_Roll_deg();

    position[0] += this->speed * direction * cos(M_PI * angle/180);
    position[1] += this->speed * direction * sin(M_PI * angle/180);
    
    pMobObj->SetPosition_m(position);
    pAccCtrl->MarkChange();
    pAccCtrl->UnlockAccess();
    usleep(100000);
  }
  
  return true;
}


/*!
 *
 */
bool Interp4Move::ReadParams(std::istream& Strm_CmdsList)
{
  Strm_CmdsList >> speed >> trip_length;
  return !Strm_CmdsList.fail();
}


/*!
 *
 */
Interp4Command* Interp4Move::CreateCmd()
{
  return new Interp4Move();
}


/*!
 *
 */
void Interp4Move::PrintSyntax() const
{
  cout << "   Move  NazwaObiektu  Szybkosc[m/s]  DlugoscDrogi[m]" << endl;
}

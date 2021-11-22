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
  double angle = pMobObj->GetAng_Yaw_deg();
  Vector3D progress = pMobObj->GetPositoin_m();
  int direction = this->speed > 0 ? 1 : -1;
  Vector3D setpoint = progress;

  setpoint[0] += this->trip_length * direction * cos(M_PI * angle/180);
  setpoint[1] += this->trip_length * direction * sin(M_PI * angle/180);

  while (setpoint[0] < progress[0] && setpoint[1] < progress[1])
  {
    pAccCtrl->LockAccess();

    progress[0] += this->speed * cos(M_PI * angle/180);
    progress[1] += this->speed * sin(M_PI * angle/180);
    
    // if (direction == 1)
    // {
    //   if (progress > setpoint)
    //   {
    //     progress = setpoint;
    //   }
    // }
    // else
    // {
    //   if (progress < setpoint)
    //   {
    //     progress = setpoint;
    //   }
    // }

    pMobObj->SetPosition_m(progress);
    pAccCtrl->MarkChange();
    pAccCtrl->UnlockAccess();
    usleep(300000);
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

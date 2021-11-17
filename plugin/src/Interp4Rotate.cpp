#include <iostream>
#include "Interp4Rotate.hh"

using std::cout;
using std::endl;


extern "C" {
 Interp4Command* CreateCmd(void);
  const char* GetCmdName() { return "Rotate"; }
}




/*!
 * \brief
 *
 *
 */
Interp4Command* CreateCmd(void)
{
  return Interp4Rotate::CreateCmd();
}


/*!
 *
 */
Interp4Rotate::Interp4Rotate(): angular_speed(0), axis_name(""), rotation_angle(0)
{}


/*!
 *
 */
void Interp4Rotate::PrintCmd() const
{
  cout << GetCmdName() << " Obj_A " << angular_speed << " " << axis_name << " " << rotation_angle << " " << endl;
}


/*!
 *
 */
const char* Interp4Rotate::GetCmdName() const
{
  return ::GetCmdName();
}


/*!
 *
 */
bool Interp4Rotate::ExecCmd( MobileObj  *pMobObj,  AccessControl *pAccCtrl) const
{
  double progress = pMobObj->GetAng_Pitch_deg();
  double setpoint = progress + this->rotation_angle;

  while (setpoint != progress)
  {
    pAccCtrl->LockAccess();

    progress += this->angular_speed;

    if (progress > setpoint)
    {
      progress = setpoint;
    }

    pMobObj->SetAng_Pitch_deg(progress);

    pAccCtrl->MarkChange();
    pAccCtrl->UnlockAccess();
    usleep(300000);
  }
  
  return true;
}


/*!
 *
 */
bool Interp4Rotate::ReadParams(std::istream& Strm_CmdsList)
{
  Strm_CmdsList >> angular_speed >> axis_name >> rotation_angle;
  return !Strm_CmdsList.fail();
}


/*!
 *
 */
Interp4Command* Interp4Rotate::CreateCmd()
{
  return new Interp4Rotate();
}


/*!
 *
 */
void Interp4Rotate::PrintSyntax() const
{
  cout << "   Rotate  NazwaObiektu  SzybkoscKatowa[deg/s]  NazwaOsi  KatObrotu[deg]" << endl;
}

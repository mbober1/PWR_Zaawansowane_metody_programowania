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
  double progress;
  char axis = this->axis_name.at(1);

  switch (axis)
  {
  case 'X':
    progress = pMobObj->GetAng_Roll_deg();
    break;

  case 'Y':
    progress = pMobObj->GetAng_Pitch_deg();
    break;

  case 'Z':
    progress = pMobObj->GetAng_Yaw_deg();
    break;
  
  default:
    std::cerr << "yyyyyyyyyyyyyyyyyyyyyyyyyyyy" << std::endl;
    break;
  }

  int direction = this->angular_speed > 0 ? 1 : -1;
  double setpoint = progress + this->rotation_angle * direction;

  while (setpoint != progress)
  {
    pAccCtrl->LockAccess();

    progress += this->angular_speed;

    if (direction == 1)
    {
      if (progress > setpoint)
      {
        progress = setpoint;
      }
    }
    else
    {
      if (progress < setpoint)
      {
        progress = setpoint;
      }
    }

    switch (axis)
    {
    case 'X':
      pMobObj->SetAng_Roll_deg(progress);
      break;

    case 'Y':
      pMobObj->SetAng_Pitch_deg(progress);
      break;

    case 'Z':
      pMobObj->SetAng_Yaw_deg(progress);
      break;
    
    default:
      std::cerr << "yyyyyyyyyyyyyyyyyyyyyyyyyyyy" << std::endl;
      break;
    }

    pAccCtrl->MarkChange();
    pAccCtrl->UnlockAccess();
    usleep(10000);
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

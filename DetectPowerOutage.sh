# This is needed so that the script has some memory between runs. No do not make the file itself just the directory.
ShutdownStorage=/volume1/SomeLocationIDK/Shutdown.txt

# Set the IP of the device that will be keeping the NAS online.
DetectionIP=192.168.2.254

# Sets the Max amount of times DetectionIP can be offline before sending shutdown command. This is scheduled to go off once every 1 min so 5 will make it end in 5 min.
MaxTimesOut=5

# Choose if you want to notify users about the impending shutdown and if it was canceled.
NotifyUsers=true

if test -f $ShutdownStorage; then
  if ping -c 1 $DetectionIP > /dev/null; then
    rm $ShutdownStorage
    echo Server shutdown has been canceled.
    if($NotifyUsers); then
      synodsmnotify @users "Shutdown canceled!!!" "Power was restored to detection Device."
    fi
    exit -1
  else
    ShutdownStorageContent=$(cat $ShutdownStorage)
    IPOutCheckCount=$(($ShutdownStorageContent+1))
    if [ "$IPOutCheckCount" -ge "$MaxTimesOut" ]; then
      echo Server shutting down due to detected power loss.
      if($NotifyUsers); then
        synodsmnotify @users "SHUTDOWN INITIATED!!!" "Server is shutting down."
      fi
      rm $ShutdownStorage
      sleep 1
      shutdown -h -q now
      exit -1
    else
      echo $IPOutCheckCount > $ShutdownStorage
      echo You have $(($MaxTimesOut-$IPOutCheckCount)) more loops till the server shuts down.
      if($NotifyUsers); then
        synodsmnotify @users "SHUTDOWN INITIATED!!!" "Powerloss still ongoing. Shutdown will be done in $(($MaxTimesOut-$IPOutCheckCount)) min unless restored."
      fi
      exit -1
    fi
  fi
else
  #if [ $ARpcombined -le 10 ] && [ $ARpcombined -ge 4 ]; then
  if ! ping -c 1 $DetectionIP > /dev/null; then
    echo Server will shut down in 5 min due to detected power loss.
    echo 0 > $ShutdownStorage
    if($NotifyUsers); then
      synodsmnotify @users "SHUTDOWN INITIATED!!!" "Powerloss detected. Shutdown will be done in $MaxTimesOut min unless restored."
    fi
    exit -1
  fi
fi

# Synology NAS with UPS safe shutdown.
This allows you to use a bad/cheep UPS with no USB IF you have a ESP8266.

Know that you can easily shut your NAS off with just the bash script however you wont be able to turn it back on automaticly.

That is what the ESP8266 is for.

## NAS Setup 1
You can just throw the bash script anywhere on your NAS as long as you have root priviliges and save the location for later.

However you need to change a few settings inside the script.

It is suggested that you change the first variable to be in the same directory as the script.

### Enable Wake On Lan(WOL)
On the NAS panel. Control Panel > Hardware & Power. 

Make sure to enable both "Restart automatically when power supply issue is fixed" AND "Enable WOL" on ether of the LAN ports.(mentally save what one you chose for the next step)

Hit Apply

### Get the MAC address
On the NAS panel. Control Panel > Info Center > Network.

On the LAN device you set WOL write down the MAC address but make sure its written with : instead of -.

While you are there also write down the IPv4 of your NAS if you didnt already know what it was(That is supposted to be static and if it isnt SET THAT UP.)


## Setting up the ESP8266
There are several things you need to install within the IDE but you should easily be able to find all of it on your own.

This script also has a fair number of variables that you need to edit at the start of the script. You WILL need to change the WiFi SSID, password, WOLMACAddr, and WOLIPAddr.

Make sure that you select an IP that should never be occupied by other devices. Mine is set to 192.168.2.254 you can set yours to whatever you want.
Make sure to save the IP for when you go back and edit the script.

Double check your work and UPLOAD to the ESP8266 and if you have 0 errors, monitor the serial output to make sure its running propperly.

## NAS Setup 2
Edit the script variable for DetectionIP to be for the IP of the ESP8266 or equivilant device.

# Set Up the bash script on the NAS
On the NAS Panel. Control Panel > Task Scheduler > Create > Scheduled Task > User-defined Script.
### General
Name the task whatever you want I named mine "Power Outage detection."

User needs to be root.

Disable the task for now.

### Schedule
Under date set to run daily.


Under Time

Leave first run time to 00:00 (midnight)

Set Frequency to Every Minute

Set Last Run Time to 23:59(so it runs once a minute ALL day.)

### Task Settings
IF you have it so that your NAS sends you emails then I HIGHLY suggest you do this.

Enable "Send run details by email" AND "Send run details only when the script terminates abnormally" so you DONT get spamed every minute after enabling it.

Under email set it like this IF you have gmail. YourEmail+NASPowerOutage@gmail.com that way it will go to your inbox and you can set it to VIP on your iphone so you get the emails telling you it is shuting down on your lock screen.

Under Run command set it to do a bash command with the full path to the script after it.

Then hit OK

## Testing the script on the NAS.
Run the script in task scheduler. wait aprox 10 seconds click on the task and under Action hit View Result. It SHOULD give you "No data" IF it detected the ESP8266 as online, and if not it will tell you that it will shutdown in some minutes.

You can easily clear that out if you just delete the shutdown.txt file it creates. for further testing if there is a problem.

I made the bash script as clutter free as I could while also giving basic information for when it sends an email or when you review the result.

If the scripts are not working as expected I should be able to help.

When you are done testing go ahead and enable the script.

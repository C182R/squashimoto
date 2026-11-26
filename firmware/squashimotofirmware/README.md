# squashimotofirmware

**Not finished.** This is the start of the controller board firmware, on hold until the parts arrive. It can't be tested or tuned without the boards and hoverboard hardware.

So far the sketch has:

- the UART link to the rear hoverboard board (EFeru command and feedback frames)
- an e-stop and link-timeout stop latch
- a torque limit and slew

Still to do once the parts are here:

- the controller input and balance loop (`controllerAlive()` and `requestedTorque()` are declared but not written yet, so the sketch doesn't compile)
- set the pins to match the controller board
- the front hoverboard boards

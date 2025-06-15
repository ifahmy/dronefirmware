#include "drivers/io.h"
#include "drivers/time.h"
#include "drivers/serial.h"
#include "drivers/system.h"
#include "drivers/usb_io.h"

#include "platform.h"
#include "target.h"

void targetConfiguration(void)
{
    IOInit(IO_TAG(PA02), OWNER_CUSTOM, 0); // RADIO_EN
    IOInit(IO_TAG(PA03), OWNER_CUSTOM, 0); // RADIO_IRQ

    IOConfigGPIO(IO_TAG(PA02), IOCFG_OUT_PP);
    IOConfigGPIO(IO_TAG(PA03), IOCFG_IPU);

    digitalHi(IO_TAG(PA02));
}

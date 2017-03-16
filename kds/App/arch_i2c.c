#include "arch_i2c.h"
#include "MKL25Z4.h"

static uint8_t error;
static uint16_t timeout;

/***********************************************************************************************\
* Private functions
\***********************************************************************************************/

/*********************************************************\
* Initiate I2C Start Condition
\*********************************************************/
static unsigned char I2C_Start(void)
{
	error = 0x00;
	I2C0_C1 |= I2C_C1_TX_MASK;
	I2C0_C1 |= I2C_C1_MST_MASK;
	timeout = 0;
	while ((!(I2C0_S & I2C_S_BUSY_MASK)) && (timeout<10000))
		timeout++;
	if (timeout >= 10000)
		error |= 0x01;
	return error;
} //*** Wait until BUSY=1


/*********************************************************\
* Initiate I2C Stop Condition
\*********************************************************/
static unsigned char I2C_Stop(void)
{
	error = 0x00;
	I2C0_C1 &= ~I2C_C1_MST_MASK;
	timeout = 0;
	while ( (I2C0_S & I2C_S_BUSY_MASK) && (timeout<10000))
		timeout++;
	if (timeout >= 10000)
		error |= 0x02;
	return error;
} //*** Wait until BUSY=0


/*********************************************************\
* Initiate I2C Repeat Start Condition
\*********************************************************/
static unsigned char I2C_RepeatStart(void)
{
	error = 0x00;
	I2C0_C1 |= I2C_C1_RSTA_MASK;
	timeout = 0;
	while ((!(I2C0_S & I2C_S_BUSY_MASK)) && (timeout<10000))
		timeout++;
	if (timeout >= 10000)
		error |= 0x04;

	return error;
} //*** Wait until BUSY=1

/*********************************************************\
* I2C Cycle Write
\*********************************************************/
static unsigned char I2C_CycleWrite(uint8_t bout)
{
	timeout = 0; 
	error = 0x00;
	while ((!(I2C0_S & I2C_S_TCF_MASK)) && (timeout<10000))
		timeout++;
	if (timeout >= 10000)
		error |= 0x08; 
	I2C0_C1 |= I2C_C1_TX_MASK;
	I2C0_D = bout; 
	timeout = 0;
	while ((!(I2C0_S & I2C_S_IICIF_MASK)) && (timeout<10000))
		timeout++;
	if (timeout >= 10000)
		error |= 0x10;
	I2C0_S |= I2C_S_IICIF_MASK;    // clear the int pending flag
	if (I2C0_S & I2C_S_RXAK_MASK)  // no ack received
		error |= 0x20;
	return error;
}


/*********************************************************\
* I2C Cycle Read
\*********************************************************/
static uint8_t I2C_CycleRead(uint8_t ack)
{
	uint8_t bread; 
	timeout = 0;
	error = 0x00;

	while ((!(I2C0_S & I2C_S_TCF_MASK)) && (timeout<10000))
		timeout++;
	if (timeout >= 10000)
		error|=0x08;
	I2C0_C1 &= ~I2C_C1_TX_MASK;     // Receive mode   
	if( ack )
	{
	  I2C0_C1 |= I2C_C1_TXAK_MASK;
	}
	else
	{
		I2C0_C1 &= ~I2C_C1_TXAK_MASK;
	}
	bread = I2C0_D; 
	timeout = 0; 
	while ((!(I2C0_S & I2C_S_IICIF_MASK)) && (timeout<10000))
		timeout++;
	if (timeout >= 10000)
		error |= 0x10;
	I2C0_S &= I2C_S_IICIF_MASK;    // clear the int pending flag

	return bread;
}

void arch_i2c_init(hal_i2c_config *conf)
{
	I2C_MemMapPtr pthisi2c;
	if(conf->index==0)
	{
		pthisi2c = I2C0_BASE_PTR;
	}
	else
	{
		//error!
		return ;
	}
	
	SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK; // enable PORTA clock
	PORTB_PCR3 = PORT_PCR_MUX(2);
	PORTB_PCR4 = PORT_PCR_MUX(2);
	
	SIM_SCGC4 |= SIM_SCGC4_I2C0_MASK;  // enable IIC0 clock
	pthisi2c->F  = 0x1f;   // about 100K baud rate
	pthisi2c->C1 = (I2C_C1_IICEN_MASK | I2C_C1_MST_MASK | I2C_C1_TX_MASK);      //master mode
}

void arch_i2c_write(hal_i2c_config *conf, uint32_t address, uint8_t *data, uint8_t length)
{	
	uint8_t i;
	I2C_Start();
	address = (address<<1);
	I2C_CycleWrite(address);
	for(i=0;i<length;i++)
		I2C_CycleWrite(*data++);
	I2C_Stop();
}

void arch_i2c_read(hal_i2c_config *conf, uint32_t address, uint8_t *data, uint8_t length)
{
	uint8_t i;
	I2C_Start();
	address = (address<<1) + 1;
	I2C_CycleWrite(address);
	for(i=0;i<length;i++)
	{
		*data = I2C_CycleRead(1);
		data++;
	}	
	I2C_Stop();
}

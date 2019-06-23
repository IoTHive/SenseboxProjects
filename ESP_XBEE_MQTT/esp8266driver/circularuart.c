/**
 * @file      circularuart.c
 * @author    Atakan S.
 * @date      01/01/2019
 * @version   1.0
 * @brief     Full-duplex UART driver based on circular buffer.
 * @TODO      Move hardware related parts into seperate file.
 *
 * @copyright Copyright (c) 2018 Atakan SARIOGLU ~ www.atakansarioglu.com
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a
 *  copy of this software and associated documentation files (the "Software"),
 *  to deal in the Software without restriction, including without limitation
 *  the rights to use, copy, modify, merge, publish, distribute, sublicense,
 *  and/or sell copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in
 *  all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 *  DEALINGS IN THE SOFTWARE.
 */

// Includes.
#include "circularuart.h"
#include "circularbuffer.h"

// Variables.
CircularBufferObject_t rxBufferObject, txBufferObject;

/*
 * @brief Initializes UART hardware with the given baud-rate.
 * @param baud The baud-rate to set.
 * @param parity Parity setting. 0 for no-parity, 1 for odd and 2 for even.
 */
void CircularUART_Init(const uint32_t baud, const uint8_t parity) {

	// Reset the buffers.
	CircularBuffer_init(&rxBufferObject, NULL, 0);
	CircularBuffer_init(&txBufferObject, NULL, 0);
}

/*
 * @brief Initializes and enables TX.
 * @param buffer Memory buffer to use for tx circular buffer.
 * @param length_2N Size of the buffer memory, i.e. 8 indicates 2^8=256 bytes.
 */
void CircularUART_StartTx(uint8_t * const buffer, const uint8_t length_2N) {

	// Initialize the buffer.
	CircularBuffer_init(&txBufferObject, buffer, length_2N);
}

/*
 * @brief Initializes and enables RX.
 * @param buffer Memory buffer to use for rx circular buffer.
 * @param length_2N Size of the buffer memory, i.e. 8 indicates 2^8=256 bytes.
 */
void CircularUART_StartRx(uint8_t * const buffer, const uint8_t length_2N) {

	// Initialize the buffer.
	CircularBuffer_init(&rxBufferObject, buffer, length_2N);

}

/*
 * @brief Clear the TX buffer and fault flag.
 */
void CircularUART_ClearTx(void) {

	// Initialize the buffer.
	CircularBuffer_checkAndClearFault(&txBufferObject, true);
}

/*
 * @brief Clear the RX buffer and fault flag.
 */
void CircularUART_ClearRx(void) {
	// Clear buffer and fault.
	CircularBuffer_checkAndClearFault(&rxBufferObject, true);
}

/*
 * @brief Triggers transmission of data.
 * @param data Data to send.
 * @param maxlen The requested length for sending data.
 * @return Returns the actual length that was copied to the tx buffer.
 */
uint8_t sendData;
uint16_t CircularUART_Send(const uint8_t * data, const uint16_t maxlen)
{
        
        struct io_descriptor *io;
        usart_async_get_io_descriptor(&USART_0, &io);
	uint16_t result = CircularBuffer_pushBack(&txBufferObject, data, maxlen);

        if (CircularBuffer_popFrontByte(&txBufferObject, &sendData)) 
        {
                io_write(io, &sendData, 1);
        } 

	return result;
}

/*
 * @brief Get the received data from rx buffer.
 * @param data Memory to write the received data.
 * @param maxlen The requested length for receiving data.
 * @return Returns the actual length that was copied from the rx buffer.
 */
uint16_t CircularUART_Receive(uint8_t * data, const uint16_t maxlen) 
{
	return CircularBuffer_popFront(&rxBufferObject, data, maxlen);
}

/*
 * @brief Get the number of bytes that are still in tx buffer.
 * @return Returns the number of unsent bytes.
 */
uint16_t CircularUART_GetUnsentCount(void) {
	return CircularBuffer_getUnreadSize(&txBufferObject);
}

/*
 * @brief Get the number of received bytes in the rx buffer.
 * @return Returns the number of unread bytes.
 */
uint16_t CircularUART_GetUnreadCount(void) {
	return CircularBuffer_getUnreadSize(&rxBufferObject);
}

/*
 * @brief Interrupt handler for RX and TX operations.
 */
void ESP_UART_SEND_IRQHandler(void) {
	//-- Transmit buffer empty interrupt.
	//if (USART_GetITStatus(USART1, USART_IT_TXE)) 
        {
		// Pop from tx buffer (if available) to UART.
		uint8_t data;
		if (CircularBuffer_popFrontByte(&txBufferObject, &data)) 
                {
			//USART_SendData(USART1, data);
		} else 
                {
			//-- Disable the USART1 transmit buffer empty interrupt.
			//USART_ITConfig(USART1, USART_IT_TXE, DISABLE);
		}
	}

	//-- Reception complete interrupt.
	//if (USART_GetITStatus(USART1, USART_IT_RXNE))
        {
		// Push from UART to rx buffer.
		//CircularBuffer_pushBackByte(&rxBufferObject, USART_ReceiveData(USART1));
	}
}

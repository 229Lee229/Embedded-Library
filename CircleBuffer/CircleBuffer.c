#include <stdint.h>
#include <stdbool.h>

// Buffer structure with count to avoid ambiguity
typedef struct {
    volatile uint32_t read_idx;
    volatile uint32_t write_idx;
    volatile uint32_t count;      // KEY: Track actual count
    uint32_t size;
    volatile uint8_t *buffer;
} uart_circular_buffer_t;

static uint8_t g_uart_data[64];
static uart_circular_buffer_t g_uart_buffer;

void buffer_init(uart_circular_buffer_t *buf, uint32_t size, uint8_t *data) {
    buf->read_idx = 0;
    buf->write_idx = 0;
    buf->count = 0;               // Start with zero count
    buf->size = size;
    buf->buffer = data;
}

// Called from interrupt - must be atomic
int buffer_write(uart_circular_buffer_t *buf, uint8_t data) {
    // Check if buffer is full using count
    if (buf->count >= buf->size) {
        return -1; // Buffer full
    }
    
    buf->buffer[buf->write_idx] = data;
    buf->write_idx = (buf->write_idx + 1) % buf->size;
    buf->count++;                 // Increment count atomically
    
    return 0;
}

// Called from main code
int buffer_read(uart_circular_buffer_t *buf, uint8_t *data) {
    uint32_t saved_interrupt_state;
    
    // Critical section for entire operation
    saved_interrupt_state = __get_interrupt_state();
    __disable_irq();
    
    if (buf->count == 0) {
        __restore_interrupt_state(saved_interrupt_state);
        return -1; // Buffer empty
    }
    
    // Keep interrupts disabled during entire read operation
    *data = buf->buffer[buf->read_idx];
    buf->read_idx = (buf->read_idx + 1) % buf->size;
    buf->count--;                 // Decrement count atomically
    
    // Only restore interrupts after complete operation
    __restore_interrupt_state(saved_interrupt_state);
    return 0;
}

// Now this is simple and race-condition free!
uint32_t buffer_available(uart_circular_buffer_t *buf) {
    return buf->count;            // Single atomic read
}

bool buffer_is_full(uart_circular_buffer_t *buf) {
    return buf->count >= buf->size;
}

bool buffer_is_empty(uart_circular_buffer_t *buf) {
    return buf->count == 0;
}

uint32_t buffer_free_space(uart_circular_buffer_t *buf) {
    return buf->size - buf->count;
}
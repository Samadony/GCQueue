
#include <GCQueue_Core.h>
#include <GCQueue_Interface.h>
#include <utils/defines.h>
#include <unity.h>
#include <stddef.h>
#include <string.h>
#include <stdint.h>

#define UTEST_TYPE_BEING_TESTED			 uint8_t
#define UTEST_GCQ_HARD_ERASE_VALUE		(UTEST_TYPE_BEING_TESTED)0xAAAAAAAAU

/*Full Encabsulation */
DEFINE_GCQUEUE(UTEST_TYPE_BEING_TESTED);
CREATE_GCQUEUE(UTEST_TYPE_BEING_TESTED, gcqueue_utest, QUEUE_BUFFER_SIZE);


/*
 * Goal, test the template against mulitple definitins and instantiations
 */
//DEFINE_GCQUEUE(uint16_t);
//DEFINE_GCQUEUE(uint32_t);
//DEFINE_GCQUEUE(uint64_t);
//DEFINE_GCQUEUE(int8_t);
//DEFINE_GCQUEUE(int16_t);
//DEFINE_GCQUEUE(int32_t);
//DEFINE_GCQUEUE(int64_t);
//
//void test_template_implementation(void)
//{
//	CREATE_GCQUEUE(uint8_t, gcqueue_utest_0, QUEUE_BUFFER_SIZE);
//	CREATE_GCQUEUE(uint16_t, gcqueue_utest_1, QUEUE_BUFFER_SIZE);
//	CREATE_GCQUEUE(uint32_t, gcqueue_utest_2, QUEUE_BUFFER_SIZE);
//	CREATE_GCQUEUE(uint64_t, gcqueue_utest_3, QUEUE_BUFFER_SIZE);
//
//	CREATE_GCQUEUE(int8_t, gcqueue_utest_4, QUEUE_BUFFER_SIZE);
//	CREATE_GCQUEUE(int16_t, gcqueue_utest_5, QUEUE_BUFFER_SIZE);
//	CREATE_GCQUEUE(int32_t, gcqueue_utest_6, QUEUE_BUFFER_SIZE);
//	CREATE_GCQUEUE(int64_t, gcqueue_utest_7, QUEUE_BUFFER_SIZE);
//
//	GCQ_HARD_ERASE_ABSTRACTOR(uint8_t, gcqueue_utest_0);
//	GCQ_SOFT_ERASE_ABSTRACTOR(TYPE, OBJECT_ADD)
//	GCQ_IS_FULL_ABSTRACTOR(TYPE, OBJECT_ADD)
//	GCQ_IS_EMPTY_ABSTRACTOR(TYPE, OBJECT_ADD)
//	GCQ_ENQUEUE_ABSTRACTOR(TYPE, OBJECT_ADD, DATA_ADD)
//	GCQ_DEQUEUE_ABSTRACTOR(TYPE, OBJECT_ADD, DATA_ADD)
//	GCQ_PEEK_ABSTRACTOR(TYPE, OBJECT_ADD, DATA_ADD)
//}



void setUp(void)
{
	gcqueue_utest.write_idx = -1;
	gcqueue_utest.read_idx = -1;
	gcqueue_utest.data_buffer_ptr = gcqueue_utest_data_buffer;
	memset(gcqueue_utest.data_buffer_ptr, UTEST_GCQ_HARD_ERASE_VALUE,
			sizeof(gcqueue_utest_data_buffer));
}

void tearDown(void)
{
	//Do Nothing
}

/*
 * Goal: 1- check whether the Hard erase is done in a proper way
 *
 * //Scenario_0
 * Arrange:
 * Act: call EraseHard_GCQueue(&gcqueue_utest_data_buffer)
 * Assert:
 * - gcq_status = Q_OK
 * - write_idx = 0
 * - read_idx  = 0
 * - data_buffer_ptr[0 -> QUEUE_BUFFER_SIZE -1 ] = QUEUE_ERASE_VALUE
 *
 * //Scenario_1
 * Arrange:
 * Act: EraseHard_GCQueue(NULL)
 * Assert:
 * - gcq_status = GCQ_NULL_BUFFER
 *
 * //Scenario_2
 * Arrange: gcq_header_utest.data_buffer_ptr = NULL
 * Act:
 * Assert:
 * - TEST_ASSERT_NULL(gcq_header_utest.data_buffer_ptr)
 * - gcq_status = GCQ_NULL_BUFFER
 *
 */
void test_HardErase_of_the_GCQueue(void)
{
	uint16_t iterator;
	GCQ_Status_t gcq_status;
/*
 * Test happy scenario
 */
	//Secenrio_0
	gcq_status = GCQ_HARD_ERASE_API(UTEST_TYPE_BEING_TESTED, &gcqueue_utest);
	TEST_ASSERT_EQUAL(GCQ_OK, gcq_status);
	TEST_ASSERT_EQUAL(gcqueue_utest.write_idx, 0);
	TEST_ASSERT_EQUAL(gcqueue_utest.read_idx, 0);
	for(iterator = 0; iterator < QUEUE_BUFFER_SIZE; iterator++)
	{
    	TEST_ASSERT_EQUAL(QUEUE_ERASE_VALUE, gcqueue_utest.data_buffer_ptr[iterator]);
	}
/*
 * Test sad scenario
 */
	//Scenario_1
	gcq_status = GCQ_HARD_ERASE_API(UTEST_TYPE_BEING_TESTED, NULL);
	TEST_ASSERT_EQUAL(GCQ_DATA_BUFFER_NULL, gcq_status);

	//Scenario_2
	gcqueue_utest.data_buffer_ptr = NULL;
	gcq_status = GCQ_HARD_ERASE_API(UTEST_TYPE_BEING_TESTED,NULL);
	TEST_ASSERT_EQUAL(GCQ_DATA_BUFFER_NULL, gcq_status);

}
/*
 * Goal: check whether the Soft erase is done in a proper way (only buffer indices are reset to 0)
 *
  * //Scenario_0
 * Arrange:
 * Act: call EraseSoft_GCQueue(&gcqueue_utest_data_buffer)
 * Assert:
 * - gcq_status = Q_OK
 * - write_idx = 0
 * - read_idx  = 0
 * - data_buffer_ptr[0 -> QUEUE_BUFFER_SIZE -1 ] = UTEST_GCQ_HARD_ERASE_VALUE
 *
 * //Scenario_1
 * Arrange:
 * Act: EraseSoft_GCQueue(NULL)
 * Assert:
 * - gcq_status = GCQ_NULL_BUFFER
 *
 * //Scenario_2
 * Arrange: gcq_header_utest.data_buffer_ptr = NULL
 * Act:
 * Assert:
 * - TEST_ASSERT_NULL(gcq_header_utest.data_buffer_ptr)
 * - gcq_status = GCQ_NULL_BUFFER
 *
 */
void test_SoftErase_of_the_GCQueue(void)
{
	uint32_t iterator;
	GCQ_Status_t gcq_status;
/*
 * Test happy scenario
 */
	//Secenrio_0
	gcq_status = GCQ_SOFT_ERASE_API(UTEST_TYPE_BEING_TESTED, &gcqueue_utest);
	TEST_ASSERT_EQUAL(GCQ_OK, gcq_status);
	TEST_ASSERT_EQUAL(gcqueue_utest.write_idx, 0);
	TEST_ASSERT_EQUAL(gcqueue_utest.read_idx, 0);

	for(iterator = 0; iterator < QUEUE_BUFFER_SIZE; iterator++)
	{
    	TEST_ASSERT_EQUAL_HEX(UTEST_GCQ_HARD_ERASE_VALUE, gcqueue_utest.data_buffer_ptr[iterator]);
	}
/*
 * Test sad scenario
 */
	//Scenario_1
	gcq_status = GCQ_HARD_ERASE_API(UTEST_TYPE_BEING_TESTED, NULL);
	TEST_ASSERT_EQUAL(GCQ_DATA_BUFFER_NULL, gcq_status);

	//Scenario_2
	gcqueue_utest.data_buffer_ptr = NULL;
	gcq_status = GCQ_SOFT_ERASE_API(UTEST_TYPE_BEING_TESTED, NULL);
	TEST_ASSERT_EQUAL(GCQ_DATA_BUFFER_NULL, gcq_status);

}
/*
 * Goal, test GCQueue_IsFull
 *
 * Scenario_0.0: the buffer is Full
 * Arrange: set read_idx =  0  write_idx = QUEUE_BUFFER_SIZE -1
 * Act: call GCQueue_IsFull
 * Assert: 	GCQ_Status_t gcq_status = GCQ_FULL
 *
 * Scenario_0.1: the buffer is Full
 * Arrange: set read_idx = x and write_idx = (x - 1) (0 =< x =< QUEUE_BUFFER_SIZE -1)
 * Act: call GCQ_IS_FULL_API(UTEST_TYPE_BEING_TESTED, )
 * Assert: 	GCQ_Status_t gcq_status = GCQ_FULL
 *
 * Scenario_1: the buffer is not Full
 * Arrange: set read_idx = write_idx = x  ( x == 5)
 * Act: GCQ_IS_FULL_API(UTEST_TYPE_BEING_TESTED, )
 * Assert: GCQ_Status_t gcq_status = GCQ_OK
 *
 * Scenario_2: the buffer is Empty
 * Arrange: set read_idx = write_idx = x  ( x == 0)
 * Act: GCQ_IS_FULL_API(UTEST_TYPE_BEING_TESTED, )
 * Assert: GCQ_Status_t gcq_status = GCQ_OK
 *
 */
void test_GCQueue_IsFull_induced_testing(void)
{
	GCQ_Status_t gcq_status;
	uint32_t random_index_within_range = 200;
	uint32_t first_index_in_buffer = 0;
	uint32_t last_index_in_buffer = QUEUE_BUFFER_SIZE -1;

	//Scenario_0.0
	gcqueue_utest.read_idx = first_index_in_buffer;
	gcqueue_utest.write_idx = last_index_in_buffer;
	gcq_status = GCQ_IS_FULL_API(UTEST_TYPE_BEING_TESTED, &gcqueue_utest);
	TEST_ASSERT_EQUAL(GCQ_FULL, gcq_status);

	//Scenario_0.1
	gcqueue_utest.read_idx = random_index_within_range;
	gcqueue_utest.write_idx = gcqueue_utest.read_idx - 1;
	gcq_status = GCQ_IS_FULL_API(UTEST_TYPE_BEING_TESTED, &gcqueue_utest);
	TEST_ASSERT_EQUAL(GCQ_FULL, gcq_status);

	//Scenario_1.0
	gcqueue_utest.write_idx = random_index_within_range;
	gcqueue_utest.read_idx = random_index_within_range + 2; // just make the difference between the 2 indices more than 1
	gcq_status = GCQ_IS_FULL_API(UTEST_TYPE_BEING_TESTED, &gcqueue_utest);
	TEST_ASSERT_EQUAL(GCQ_OK, gcq_status);

	//Scenario_2.0
	/*
	 * Note: I deliberately assigned write_idx first then read_idx, since read
	 * should catch up with the write_idx but the write_idx should never catch up
	 * with the read_idx UNLESS over writing is enabled.
	 * TODO: Disable this test when over writing is enabled and enable it when
	 * overwritng is disabled
	 */
	gcqueue_utest.write_idx = random_index_within_range;
	gcqueue_utest.read_idx = gcqueue_utest.write_idx ;
	gcq_status = GCQ_IS_FULL_API(UTEST_TYPE_BEING_TESTED, &gcqueue_utest);
	TEST_ASSERT_EQUAL(GCQ_OK, gcq_status);

	//Scenario_2.1
	/*
	 * Empty case, both idxs = 0
	 */
	gcqueue_utest.write_idx = first_index_in_buffer;
	gcqueue_utest.read_idx = first_index_in_buffer;
	gcq_status = GCQ_IS_FULL_API(UTEST_TYPE_BEING_TESTED, &gcqueue_utest);
	TEST_ASSERT_EQUAL(GCQ_OK, gcq_status);
}

/*
 * Goal, test GCQ_IS_EMPTY_API(UTEST_TYPE_BEING_TESTED, )
 *
 * Scenario_0: the buffer is Empty
 * Arrange: set read_idx = write_idx = 0
 * Act: call GCQ_IS_EMPTY_API(UTEST_TYPE_BEING_TESTED, )
 * Assert: 	GCQ_Status_t gcq_status = GCQ_Empty
 *
 * Scenario_1: the buffer is not empty
 * Arrange: set read_idx = random_number_within_size and write_idx = read_idx + 2,
 * just both number shall be with difference more than 1
 * Act: call GCQ_IS_EMPTY_API(UTEST_TYPE_BEING_TESTED, )
 * Assert: 	GCQ_Status_t gcq_status = GCQ_FULL
 *
 * Scenario_2: the buffer is Full
 * Arrange: set read_idx = 0 and write_idx = size - 1
 * Act: call GCQ_IS_EMPTY_API(UTEST_TYPE_BEING_TESTED, )
 * Assert: 	GCQ_Status_t gcq_status = GCQ_FULL
 *
 *
 *
 */
void test_GCQueue_IsEmpty_induced_testing(void)
{
	GCQ_Status_t gcq_status;
	uint32_t random_index_within_range = 200;
	uint32_t first_index_in_buffer = 0;
	uint32_t last_index_in_buffer = QUEUE_BUFFER_SIZE -1;
	uint32_t idx_diff = 2;

	//Scenario_0.0
	gcqueue_utest.read_idx = first_index_in_buffer;
	gcqueue_utest.write_idx = first_index_in_buffer;
	gcq_status = GCQ_IS_EMPTY_API(UTEST_TYPE_BEING_TESTED, &gcqueue_utest);
	TEST_ASSERT_EQUAL(GCQ_EMPTY, gcq_status);

	//Scenario_0.1
	gcqueue_utest.read_idx = random_index_within_range;
	gcqueue_utest.write_idx = random_index_within_range;
	gcq_status = GCQ_IS_EMPTY_API(UTEST_TYPE_BEING_TESTED, &gcqueue_utest);
	TEST_ASSERT_EQUAL(GCQ_EMPTY, gcq_status);

	//Scenario_0.2
	gcqueue_utest.write_idx = last_index_in_buffer;
	gcqueue_utest.read_idx = last_index_in_buffer;
	gcq_status = GCQ_IS_EMPTY_API(UTEST_TYPE_BEING_TESTED, &gcqueue_utest);
	TEST_ASSERT_EQUAL(GCQ_EMPTY, gcq_status);

	//Scenario_1.0
	/*
	 * Note: I deliberately assigned write_idx first then read_idx, since read
	 * should catch up with the write_idx but the write_idx should never catch up
	 * with the read_idx UNLESS over writing is enabled.
	 * TODO: Disable this test when over writing is enabled and enable it when
	 * overwritng is disabled
	 */
	gcqueue_utest.write_idx = random_index_within_range; //random < size -2 (at least)
	gcqueue_utest.read_idx = random_index_within_range - idx_diff ; // diff more than 1
	gcq_status = GCQ_IS_EMPTY_API(UTEST_TYPE_BEING_TESTED, &gcqueue_utest);
	TEST_ASSERT_EQUAL(GCQ_OK, gcq_status);

	//Scenario 1.1
	gcqueue_utest.write_idx = first_index_in_buffer; //random < size -2 (at least)
	gcqueue_utest.read_idx = last_index_in_buffer ; // diff more than 1
	gcq_status = GCQ_IS_EMPTY_API(UTEST_TYPE_BEING_TESTED, &gcqueue_utest);
	TEST_ASSERT_EQUAL(GCQ_OK, gcq_status);
}

/*
 *Goal, Enqueue untill the buffer is full with known pattern
 *
 * Scenario_0.0, fill the buffer till full
 * Arrange: Har
 * Act: Call GCQ_ENQUEUE_API(UTEST_TYPE_BEING_TESTED, ) in loop equal to the array`s (size -1)
 * Assert: the outcome shall be always gcq_status = GCQ_OK
 *
 * Assert: check if it full
 * Assert: all data of the buffer shall be enqueued_data = 1377
 */
void test_GCQ_ENQUEUE_API(void)
{
	GCQ_Status_t gcq_status;
	uint32_t iterator = 0;
	UTEST_TYPE_BEING_TESTED enqueued_data = 137;//random u8 number
	//Scenario_0.0
	gcq_status = GCQ_HARD_ERASE_API(UTEST_TYPE_BEING_TESTED, &gcqueue_utest);
	TEST_ASSERT_EQUAL(GCQ_OK, gcq_status);
	for(iterator = 0 ; iterator < (QUEUE_BUFFER_SIZE-1) ; iterator++)
	{
		gcq_status = GCQ_ENQUEUE_API(UTEST_TYPE_BEING_TESTED, &gcqueue_utest, &enqueued_data);
		TEST_ASSERT_EQUAL(GCQ_OK, gcq_status);
	}
	for(iterator = 0 ; iterator < (QUEUE_BUFFER_SIZE-1) ; iterator++)
	{
		TEST_ASSERT_EQUAL(enqueued_data, gcqueue_utest.data_buffer_ptr[iterator]);
	}
	//Its now Full queue, Enqueue One more time expecting a full status
	gcq_status = GCQ_ENQUEUE_API(UTEST_TYPE_BEING_TESTED, &gcqueue_utest, &enqueued_data);
	TEST_ASSERT_EQUAL(GCQ_FULL, gcq_status);
	//Make sure our buffer isnt touched (test data integrity) after a full status
	for(iterator = 0 ; iterator < (QUEUE_BUFFER_SIZE-1) ; iterator++)
	{
		TEST_ASSERT_EQUAL(enqueued_data, gcqueue_utest.data_buffer_ptr[iterator]);
	}
}

/*
 *Goal, Dequeue untill the buffer is empty with known pattern
 *
 * Scenario_0.0, dequeue untill empty
 * Arrange: Enqueue till Full
 * Act: Call GCQ_DEQUEUE_API(UTEST_TYPE_BEING_TESTED, ) in loop equal to the array size -1
 * Assert: the outcome shall be always gcq_status = GCQ_OK
 *
 * Scenario_1.0, Arrange a mixed enqueue, dequeue request
 *
 *
 */
void test_GCQ_DEQUEUE_API(void)
{
	GCQ_Status_t gcq_status;
	uint32_t iterator;
	UTEST_TYPE_BEING_TESTED enqueued_data = 137;//random u8 number
	UTEST_TYPE_BEING_TESTED dequeued_data = 0;//random u8 number

	//Scenario_0.0
	for(iterator = 0 ; iterator < (QUEUE_BUFFER_SIZE-1) ; iterator++)
	{
		gcq_status = GCQ_ENQUEUE_API(UTEST_TYPE_BEING_TESTED, &gcqueue_utest, &enqueued_data);
		TEST_ASSERT_EQUAL(GCQ_OK, gcq_status);
	}
	for(iterator = 0 ; iterator < (QUEUE_BUFFER_SIZE-1) ; iterator++)
	{
		gcq_status = GCQ_DEQUEUE_API(UTEST_TYPE_BEING_TESTED, &gcqueue_utest, &dequeued_data);
		TEST_ASSERT_EQUAL(GCQ_OK, gcq_status);
		TEST_ASSERT_EQUAL(enqueued_data, dequeued_data);
	}
	/*
	 * One more dequeue, the status shall be Empty
	 */
	gcq_status = GCQ_DEQUEUE_API(UTEST_TYPE_BEING_TESTED, &gcqueue_utest, &dequeued_data);
	TEST_ASSERT_EQUAL(GCQ_EMPTY, gcq_status);
	TEST_ASSERT_EQUAL(enqueued_data, dequeued_data);

	//Scenario_1.0
	for(iterator = 0 ; iterator < ((QUEUE_BUFFER_SIZE-1)) ; iterator++)
	{
		gcq_status = GCQ_ENQUEUE_API(UTEST_TYPE_BEING_TESTED, &gcqueue_utest, &enqueued_data);
		TEST_ASSERT_EQUAL(GCQ_OK, gcq_status);
	}
	for(iterator = 0 ; iterator < ((QUEUE_BUFFER_SIZE-1)) ; iterator++)
	{
		gcq_status = GCQ_DEQUEUE_API(UTEST_TYPE_BEING_TESTED, &gcqueue_utest, &dequeued_data);
		TEST_ASSERT_EQUAL(GCQ_OK, gcq_status);
		TEST_ASSERT_EQUAL(enqueued_data, dequeued_data);
	}
	for(iterator = 0 ; iterator < ((QUEUE_BUFFER_SIZE-1)/2) ; iterator++)
	{
		gcq_status = GCQ_ENQUEUE_API(UTEST_TYPE_BEING_TESTED, &gcqueue_utest, &enqueued_data);
		TEST_ASSERT_EQUAL(GCQ_OK, gcq_status);
	}
	for(iterator = 0 ; iterator < ((QUEUE_BUFFER_SIZE-1)/4) ; iterator++)
	{
		gcq_status = GCQ_ENQUEUE_API(UTEST_TYPE_BEING_TESTED, &gcqueue_utest, &enqueued_data);
		TEST_ASSERT_EQUAL(GCQ_OK, gcq_status);
	}
	/*
	 * TODO:Check again
	 */
//	gcq_status = GCQ_ENQUEUE_API(UTEST_TYPE_BEING_TESTED, &gcq_header_utest, &enqueued_data);
//	TEST_ASSERT_EQUAL(GCQ_OK, gcq_status);
//	gcq_status = GCQ_ENQUEUE_API(UTEST_TYPE_BEING_TESTED, &gcq_header_utest, &enqueued_data);
//	TEST_ASSERT_EQUAL(GCQ_FULL, gcq_status);
}

/*
 *Goal, Dequeue untill the buffer is empty with known pattern
 *
 * Scenario_0.0, dequeue untill empty
 * Arrange: Arrange input array 0 to size -1
 * Act: Enqueue till Full, peek, dequeue ... iterate, iterations =  size -1
 * Assert: the outcome shall be always gcq_status = GCQ_OK
 *
 * Scenario_1.0, Arrange a mixed enqueue, dequeue request
 */
void test_GCQ_PEEK_API(void)
{

	GCQ_Status_t gcq_status;
	uint32_t iterator;
	UTEST_TYPE_BEING_TESTED enqueued_data[QUEUE_BUFFER_SIZE-1];//random u8 number
	UTEST_TYPE_BEING_TESTED peeked_data = 0;//random u8 number
	UTEST_TYPE_BEING_TESTED dequeued_data;

	//Scenario_0.0
	//Arrange

	for(iterator = 0 ; iterator < QUEUE_BUFFER_SIZE-1 ; iterator++)
	{
		enqueued_data[iterator] = iterator;
	}
	//Act
	//Assert
	for(iterator = 0 ; iterator < QUEUE_BUFFER_SIZE-2 ; iterator++)
	{
		gcq_status = GCQ_ENQUEUE_API(UTEST_TYPE_BEING_TESTED, &gcqueue_utest, &enqueued_data[iterator]);
		TEST_ASSERT_EQUAL(GCQ_OK, gcq_status);

		gcq_status = GCQ_PEEK_API(UTEST_TYPE_BEING_TESTED, &gcqueue_utest, &peeked_data);
		TEST_ASSERT_EQUAL(GCQ_OK, gcq_status);
		TEST_ASSERT_EQUAL(enqueued_data[iterator], peeked_data);

		gcq_status = GCQ_DEQUEUE_API(UTEST_TYPE_BEING_TESTED, &gcqueue_utest, &dequeued_data);
		TEST_ASSERT_EQUAL(GCQ_OK, gcq_status);
		TEST_ASSERT_EQUAL(enqueued_data[iterator], dequeued_data);
	}
	//now the buffer shall be empty
	gcq_status = GCQ_PEEK_API(UTEST_TYPE_BEING_TESTED, &gcqueue_utest, &peeked_data);
	TEST_ASSERT_EQUAL(GCQ_EMPTY, gcq_status);
	TEST_ASSERT_EQUAL(enqueued_data[iterator -1], peeked_data);

}
typedef struct {
	uint8_t x;
	uint8_t y;
}Ahmed;

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_HardErase_of_the_GCQueue);
    RUN_TEST(test_SoftErase_of_the_GCQueue);
    RUN_TEST(test_GCQueue_IsFull_induced_testing);
    RUN_TEST(test_GCQueue_IsEmpty_induced_testing);
    RUN_TEST(test_GCQ_ENQUEUE_API);
    RUN_TEST(test_GCQ_DEQUEUE_API);
    RUN_TEST(test_GCQ_PEEK_API);
    return UNITY_END();
}

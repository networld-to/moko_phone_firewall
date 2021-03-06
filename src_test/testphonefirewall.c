/*
 * testphonefirewall.c
 *
 * (C) 2008 by MokSec Project
 * Written by Alex Oberhauser <oberhauseralex@networld.to>
 * All Rights Reserved
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 2 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with MokSec.  If not, see <http://www.gnu.org/licenses/>
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sqlite3.h>
#include <CUnit/Basic.h>
#include <CUnit/Automated.h>
#include "../src/libphonefirewall.h"


void test_add_blacklist_entry(void)
{
#if 1
	/* [OK]    -> Testuser 1:  Number in Italy. */
	CU_ASSERT(add_entry(39, 328, 123456789, "Testuser 1", "", 0, BLACKLIST_FLAG) == 0);

        /* [OK]    -> Temporary User */
	CU_ASSERT(add_entry(39, 328, 100056789, "Testuser X", "He calls always at night.", 0, BLACKLIST_FLAG) == 0);

	/* [FAILS] -> Testuser -1: The same number as "Testuser 1". */
	CU_ASSERT(add_entry(39, 328, 123456789, "Testuser -1", "Mad guy.", 0, BLACKLIST_FLAG) == -1);

	/* [FAILS] -> Testuser -1: The country code is NULL. */
	CU_ASSERT(add_entry(0, 328, 123456782, "Testuser -1", "Wants only support for his Windows system.", 0, BLACKLIST_FLAG) == -1);

	/* [FAILS] -> Testuser -1: The area code is NULL. */
	CU_ASSERT(add_entry(39, 0, 123456782, "Testuser -1", "I don't like him.", 0, BLACKLIST_FLAG) == -1);

	/* [FAILS] -> Testuser -1: The area code is NULL. */
	CU_ASSERT(add_entry(39, 328, 0, "Testuser -1", "I don't like him.", 0, BLACKLIST_FLAG) == -1);

	/* [OK]    -> Testuser 2:  The same area code and number as "Testuser
	 * 1" but a different country code. */
	CU_ASSERT(add_entry(49, 328, 123456789, "Testuser 2", "Wants only support for his Windows system..", 0, BLACKLIST_FLAG) == 0);

	/* [OK]    -> Testuser 3:  The same country code and number as "Testuser
	 * 1" but a different area code. */
	CU_ASSERT(add_entry(49, 329, 123456789, "Testuser 3", "I don't like him.", 0, BLACKLIST_FLAG) == 0);

	/* [OK]    -> NULL      :  Username is empty. */
	CU_ASSERT(add_entry(49, 329, 123456780, NULL, "I don't like him.", 0, BLACKLIST_FLAG) == 0);

	/* [OK]    -> Testuser 4:  Reason is empty. */
	CU_ASSERT(add_entry(49, 329, 123456781, "Testuser 4", "öäüß$$$$", 0, BLACKLIST_FLAG) == 0);

	/* [OK]    -> Testuser 5:  Priority is 2, which is higher than normal (0) . */
	CU_ASSERT(add_entry(49, 329, 222222222, "Testuser 5", NULL, 2, BLACKLIST_FLAG) == 0);

	/* [OK]    -> Testuser 6:  Priority is 2, which is higher than normal (0) . */
	CU_ASSERT(add_entry(49, 329, 999999999, "Testuser 6", NULL, PRIO_ALL, BLACKLIST_FLAG) == 0);
#endif
}

void test_change_blacklist_name(void)
{
#if 1
        /* [OK]    -> Testuser 5: Change "Testuser 5" to "New Testuser 5" */
        CU_ASSERT(change_name(49, 329, 222222222, "New Testuser 5", BLACKLIST_FLAG) == 1);
#endif
}

void test_rm_blacklist_entry(void)
{
#if 1
	CU_ASSERT(rm_entry(49, 329, 999999999, BLACKLIST_FLAG) == 0);
	CU_ASSERT(rm_entry(39, 328, 123456789, BLACKLIST_FLAG) == 0);
#endif
}

void test_add_whitelist_entry(void)
{
#if 1
	/* [OK]    -> Testuser 1:  Number in Italy. */
	CU_ASSERT(add_entry(39, 128, 123456789, "Testuser 1", "I like him.", 0, WHITELIST_FLAG) == 0);

	/* [FAILS] -> Testuser -1: The same number as "Testuser 1". */
	CU_ASSERT(add_entry(39, 128, 123456789, "Testuser -1", "She is a family member.", 0, WHITELIST_FLAG) == -1);

	/* [FAILS] -> Testuser -1: The country code is NULL. */
	CU_ASSERT(add_entry(0, 128, 123456782, "Testuser -1", "My buddy.", 0, WHITELIST_FLAG) == -1);

	/* [FAILS] -> Testuser -1: The area code is NULL. */
	CU_ASSERT(add_entry(39, 0, 123456782, "Testuser -1", "Nice guy.", 0, WHITELIST_FLAG) == -1);

	/* [FAILS] -> Testuser -1: The area code is NULL. */
	CU_ASSERT(add_entry(39, 128, 0, "Testuser -1", "He owes me money.", 0, WHITELIST_FLAG) == -1);

	/* [OK]    -> Testuser 2:  The same area code and number as "Testuser
	 * 1" but a different country code. */
	CU_ASSERT(add_entry(49, 128, 123456789, "Testuser 2", "I like her.", 0, WHITELIST_FLAG) == 0);

	/* [OK]    -> Testuser 3:  The same country code and number as "Testuser
	 * 1" but a different area code. */
	CU_ASSERT(add_entry(49, 129, 123456789, "Testuser 3", "My wife.", 0, WHITELIST_FLAG) == 0);

	/* [OK]    -> NULL      :  Username is empty. */
	CU_ASSERT(add_entry(49, 129, 123456780, NULL, "My girlfriend.", 0, WHITELIST_FLAG) == 0);

	/* [OK]    -> Testuser 4:  Reason is empty. */
	CU_ASSERT(add_entry(49, 129, 123456781, "Testuser 4", "Another buddy.", 0, WHITELIST_FLAG) == 0);

	/* [OK]    -> Testuser 5:  Priority is 2, which is higher than normal (0) . */
	CU_ASSERT(add_entry(49, 129, 222222222, "Testuser 5", NULL, 2, WHITELIST_FLAG) == 0);

	/* [OK]    -> Testuser 6:  Priority is 2, which is higher than normal (0) . */
	CU_ASSERT(add_entry(49, 129, 999999999, "Testuser 6", NULL, PRIO_ALL, WHITELIST_FLAG) == 0);

	/* [OK]    -> Testuser 7:  Number in Italy. */
	CU_ASSERT(add_entry(39, 128, 123456783, "Testuser 7", "", 2, WHITELIST_FLAG) == 0);

	/* [OK]    -> Testuser 8:  Number in Italy. */
	CU_ASSERT(add_entry(39, 128, 123456784, "Testuser 8", "I like him.", 5, WHITELIST_FLAG) == 0);

	/* [OK]    -> Testuser 9:  Number in Italy. */
	CU_ASSERT(add_entry(39, 128, 123456785, "Testuser 9", "I like him.", 10, WHITELIST_FLAG) == 0);
#endif
}

void test_change_whitelist_name(void)
{
#if 1
        /* [OK]    -> Testuser 5: Change "Testuser 5" to "Newly Created Testuser ÖÄß" */
        CU_ASSERT(change_name(49, 129, 222222222, "Newly Created Testuser ÖÄß", WHITELIST_FLAG));
#endif
}

void test_rm_whitelist_entry(void)
{
#if 1
	CU_ASSERT(rm_entry(49, 129, 999999999, WHITELIST_FLAG) == 0);
	CU_ASSERT(rm_entry(39, 128, 123456789, WHITELIST_FLAG) == 0);
#endif
}

void test_check_blacklist_entry(void)
{
#if 1
	CU_ASSERT(check_entry(39, 328, 123456789, 0, BLACKLIST_FLAG) == 1);
	CU_ASSERT(check_entry(39, 328, 103456785, 0, BLACKLIST_FLAG) == 0);
	CU_ASSERT(check_entry(49, 329, 999999999, 0, BLACKLIST_FLAG) == 1);
	CU_ASSERT(check_entry(49, 329, 222222222, 0, BLACKLIST_FLAG) == 0);
	CU_ASSERT(check_entry(49, 329, 222222222, 2, BLACKLIST_FLAG) == 1);
	CU_ASSERT(check_entry(49, 329, 222222222, 3, BLACKLIST_FLAG) == 1);
#endif
}

void test_check_blacklist_entry_string(void)
{
#if 1
	CU_ASSERT(check_entry_string("39328123456789", 0, BLACKLIST_FLAG) == 1);
	CU_ASSERT(check_entry_string("39328103456785", 0, BLACKLIST_FLAG) == 0);
	CU_ASSERT(check_entry_string("49329999999999", 0, BLACKLIST_FLAG) == 1);
	CU_ASSERT(check_entry_string("49329222222222", 0, BLACKLIST_FLAG) == 0);
	CU_ASSERT(check_entry_string("49329222222222", 2, BLACKLIST_FLAG) == 1);
	CU_ASSERT(check_entry_string("49329222222222", 3, BLACKLIST_FLAG) == 1);
#endif
}

void test_check_whitelist_entry(void)
{
#if 1
	CU_ASSERT(check_entry(39, 128, 123456789, 0, WHITELIST_FLAG) == 1);
	CU_ASSERT(check_entry(39, 128, 103456785, 0, WHITELIST_FLAG) == 0);
	CU_ASSERT(check_entry(49, 129, 999999999, 0, WHITELIST_FLAG) == 1);
	CU_ASSERT(check_entry(49, 129, 222222222, 0, WHITELIST_FLAG) == 0);
	CU_ASSERT(check_entry(49, 129, 222222222, 2, WHITELIST_FLAG) == 1);
	CU_ASSERT(check_entry(49, 129, 222222222, 3, WHITELIST_FLAG) == 1);
#endif
}

void test_check_whitelist_entry_string(void)
{
#if 1
	CU_ASSERT(check_entry_string("39128123456789", 0, WHITELIST_FLAG) == 1);
	CU_ASSERT(check_entry_string("39128103456785", 0, WHITELIST_FLAG) == 0);
	CU_ASSERT(check_entry_string("49129999999999", 0, WHITELIST_FLAG) == 1);
	CU_ASSERT(check_entry_string("49129222222222", 0, WHITELIST_FLAG) == 0);
	CU_ASSERT(check_entry_string("49129222222222", 2, WHITELIST_FLAG) == 1);
	CU_ASSERT(check_entry_string("49129222222222", 3, WHITELIST_FLAG) == 1);
#endif
}

void test_get_blacklist_entry_by_name(void)
{
#if 0
        struct Entry *tmp_entry = NULL;
	tmp_entry = get_entry_by_name("", BLACKLIST_FLAG);
        int count = 0;
        printf("\n");
        while ( tmp_entry != NULL ) {
                printf("[CUNIT] result #%d: +%d %d %llu - %s - %s\n", count,
                                                                      tmp_entry->country_code,
                                                                      tmp_entry->area_code,
                                                                      tmp_entry->number,
                                                                      tmp_entry->name,
                                                                      tmp_entry->reason);
                tmp_entry = tmp_entry->next;
                count++;
        }
        printf("\n");
        free(tmp_entry);
#endif
}

void test_get_whitelist_entry_by_name(void)
{
#if 0
        struct Entry *tmp_entry = NULL;
	tmp_entry = get_entry_by_name("", WHITELIST_FLAG);
        int count = 0;
        printf("\n");
        while ( tmp_entry != NULL ) {
                printf("[CUNIT] result #%d: %d: +%d %d %llu - %s - %s\n", count,
                                                                      tmp_entry->priority,
                                                                      tmp_entry->country_code,
                                                                      tmp_entry->area_code,
                                                                      tmp_entry->number,
                                                                      tmp_entry->name,
                                                                      tmp_entry->reason);
                tmp_entry = tmp_entry->next;
                count++;
        }
        printf("\n");
        free(tmp_entry);
#endif
}

int init(void)
{
        sqlite3 *db;
        char stmt[STMT_SIZE];
        int rc;

        rc = sqlite3_open(DB_FILE, &db);

        if ( rc ) {
                printf("Can't open database: %s", sqlite3_errmsg(db));
                return -1;
        }

        sprintf(stmt, "CREATE TABLE IF NOT EXISTS whitelist ( priority INTEGER, ");
        strcat(stmt, "countrycode INTEGER, ");
        strcat(stmt, "areacode INTEGER, ");
        strcat(stmt, "number BIGINT, ");
        strcat(stmt, "name varchar(64), ");
        strcat(stmt, "reason varchar(256), ");
        strcat(stmt, "PRIMARY KEY(countrycode, areacode, number) );");

        rc = sqlite3_exec(db, stmt, NULL, 0, NULL);

        if ( SQLITE_OK != rc ) {
                printf("SQL error: %s", sqlite3_errmsg(db));
        }

        sprintf(stmt, "CREATE TABLE IF NOT EXISTS blacklist ( priority INTEGER, ");
        strcat(stmt, "countrycode INTEGER, ");
        strcat(stmt, "areacode INTEGER, ");
        strcat(stmt, "number BIGINT, ");
        strcat(stmt, "name varchar(64), ");
        strcat(stmt, "reason varchar(256), ");
        strcat(stmt, "PRIMARY KEY(countrycode, areacode, number) );");

        rc = sqlite3_exec(db, stmt, NULL, 0, NULL);

        if ( SQLITE_OK != rc ) {
                printf("SQL error: %s", sqlite3_errmsg(db));
        }

        sqlite3_close(db);

        return 0;
}

int cleanup(void)
{
        if (remove(DB_FILE) != 0) {
                printf("Database file couldn't be deleted.\n");
        }
        return 0;
}

int main(int argc, char *argv[])
{
	CU_pSuite adminSuite = NULL;
	CU_pSuite searchSuite = NULL;

	CU_initialize_registry();

        /*
         * The first test suite should call the init(void) function for the
         * creation of the database and the last test suite should call the
         * cleanup(void) function to remove the database. So it's always sure
         * that we have a clean testing environment.
         */
        adminSuite = CU_add_suite("Testing Phone Firewall - administration features (add, remove, change and check)", init, NULL);
	CU_add_test(adminSuite, "test of add_blacklist_entry()", test_add_blacklist_entry);
	CU_add_test(adminSuite, "test of add_whitelist_entry()", test_add_whitelist_entry);
	CU_add_test(adminSuite, "test of check_whitelist_entry()", test_check_whitelist_entry);
	CU_add_test(adminSuite, "test of check_whitelist_entry_string()", test_check_whitelist_entry_string);
	CU_add_test(adminSuite, "test of check_blacklist_entry()", test_check_blacklist_entry);
	CU_add_test(adminSuite, "test of check_blacklist_entry_string()", test_check_blacklist_entry_string);
        CU_add_test(adminSuite, "test of change_blacklist_name()", test_change_blacklist_name);
        CU_add_test(adminSuite, "test of change_withelist_name()", test_change_whitelist_name);
	CU_add_test(adminSuite, "test of rm_blacklist_entry()", test_rm_blacklist_entry);
	CU_add_test(adminSuite, "test of rm_whitelist_entry()", test_rm_whitelist_entry);

	searchSuite = CU_add_suite("Testing Phone Firewall - searching features (by name, by number ...)", NULL, cleanup);
	CU_add_test(searchSuite, "test of get_blacklist_entry_by_name()", test_get_blacklist_entry_by_name);
	CU_add_test(searchSuite, "test of get_whitelist_entry_by_name()", test_get_whitelist_entry_by_name);

        CU_set_output_filename("tests/CUnitAutomated");
        CU_automated_run_tests();
        CU_list_tests_to_file();

        int ret = CU_get_number_of_failures();
        if ( 0 != ret ) {
                CU_basic_show_failures(CU_get_failure_list());
                printf("\n");
        } else
                printf("Congratulation, all tests run successfully!\n");

	CU_cleanup_registry();

	return ret;
}

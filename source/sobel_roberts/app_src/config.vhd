library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

package config is

constant MON_1ST : integer := 0;
constant MON_2ND : integer := 0;
constant MON_3RD : integer := 0;

-- first level parts
constant EN_EVMON_1ST: integer := 1;
constant EN_TIMEMON_1ST: integer := 0;

-- second level parts
constant EN_EVMON_2ND: integer := 0;
constant EN_TIMEMON_2ND: integer := 1;

-- third level parts
constant EN_EVMON_3RD: integer := 1;
constant EN_TIMEMON_3RD: integer := 0;

-- id area
constant EVENT_ATTR: std_logic_vector(4 downto 0) := "11100"; --1C
constant ACC_ID: std_logic_vector(3 downto 0) := "0001";

end;

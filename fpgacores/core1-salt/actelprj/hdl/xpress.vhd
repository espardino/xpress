library ieee; 
use ieee.std_logic_1164.all; 
package xpress is

  constant bus_width : integer := 16;
  constant address_lines: integer :=6;
  constant mem_depth : integer:= 2**address_lines;

  -- user defined data types 
  type mem is array (mem_depth-1 downto 0) of std_logic_vector(15 downto 0);

  -- components
 	component memory_bus_ctl is
		port (
	      -- HOST connections
		  ADDR_in: in std_logic_vector (5 downto 0);
		  nCS_in: in std_logic_vector (1 downto 0);
	      nOE_in: in std_logic;
	      nWE: in std_logic;
	      DATA_io: inout std_logic_vector (15 downto 0);
	      
	      registers: out mem; -- registers stored from HOST writes
	      memory_map: in mem  -- memory map to be served to HOST
	      
	      );
	end component;
 
    component prescaled_clock is
    	port (CLK_in: in std_logic;
    	      clock_out: out std_logic_vector (15 downto 0);
	     	  zero_out: out std_logic;
    	      nRESET_in: in std_logic;
    		  prescaler_val: in std_logic_vector(3 downto 0));
    end component;
    
    component GPIOPORT is
    generic( bitsize : integer:=16);
    	port ( PINS_io: inout std_logic_vector(bitsize-1 downto 0);
    	      value_in: in std_logic_vector(bitsize-1 downto 0);
    	      tris_in : in std_logic_vector(bitsize-1 downto 0);
              value_out: in std_logic_vector(bitsize-1 downto 0)
    	);
    end component;
    
    component PWMOUT is
    generic(     skipbits : integer := 0   );
	port (RESET_in: in std_logic;
		  CLK_in: in std_logic;
	      clock_in: in std_logic_vector (15 downto 0);
	      zero_in: in std_logic;
	      value_in: std_logic_vector(15-skipbits downto 0);
	      PWM_out: out std_logic);
	end component;

end xpress;

-- functions can be defined here 
package body xpress is 
 
end xpress; 
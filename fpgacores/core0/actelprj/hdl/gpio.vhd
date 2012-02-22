library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use work.all;

entity SingleGPIO is
	port(
		PIN_io: inout std_logic;
		value_in: in std_logic;
		tris_in: in std_logic;
		value_out: out std_logic
	);
end entity SingleGPIO;

architecture RTL of SingleGPIO is
begin

	gpio:process(value_in,tris_in)
	begin
		if tris_in='1' then
			PIN_io <= value_in;
		else
			PIN_io <='Z';
		end if;
	end process;

	value_out <=PIN_io;

end architecture RTL;


library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use work.all;


entity GPIOPORT is
   generic( bitsize : integer:=16);
    	port (PINS_io: inout std_logic_vector(bitsize-1 downto 0);
    	      value_in: in std_logic_vector(bitsize-1 downto 0);
    	      tris_in : in std_logic_vector(bitsize-1 downto 0);
    	      value_out: inout std_logic_vector(bitsize-1 downto 0)
    	);
end entity GPIOPORT;

architecture RTL of GPIOPORT is

component SingleGPIO is
	port(
		PIN_io: inout std_logic;
		value_in: in std_logic;
		tris_in: in std_logic;
		value_out: out std_logic
	);
end component;

begin

  gpios: for n in bitsize-1 downto 0 
        generate
             gpio_u: SingleGPIO port map (PINS_io(n),value_in(n),tris_in(n),value_out(n)); 
        end generate gpios;
	
end architecture RTL;
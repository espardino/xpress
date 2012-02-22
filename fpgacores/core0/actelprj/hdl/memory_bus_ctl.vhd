library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use work.all;
use work.xpress.all;

entity memory_bus_ctl is
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
end entity memory_bus_ctl;

architecture RTL of memory_bus_ctl is
	signal address_i: integer range  mem_depth-1 to 0;
begin
	--
	-- for memory access cycles see: 
	--
	-- lpc3130_3131_ds_en.pdf  pages 47-48  (section 9.2)
	--
	-- Address Latch block: on nWE or nOE falling edges
	address_latch:process (ADDR_in,nWE, nOE_in)
			begin

	            if (falling_edge(nOE_in) or falling_edge(nWE)) then
	                address_i <= to_integer(unsigned(ADDR_in(5 downto 0)));
			    end if;
			end process;
	-- Memory Write Block: on nWE rising edge when /CS asserted
	register_latch:process (nWE)
			begin
				if (nCS_in(0) = '0' and rising_edge(nWE)) then
	 				registers(address_i) <= DATA_io;
	 			end if;
	 		end process;
	-- Tri-State Buffer control
	DATA_io <= memory_map(address_i) when (nCS_in(0) = '0' and nOE_in = '0' and nWE = '1') 
	                   else (others=>'Z');
end architecture RTL;
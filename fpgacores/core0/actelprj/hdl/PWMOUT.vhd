library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use work.all;

entity PWMOUT is
   generic(     skipbits : integer := 0   );
	port (RESET_in: in std_logic;
		  CLK_in: in std_logic;
	      clock_in: in std_logic_vector (15 downto 0);
	      zero_in: in std_logic;
	      value_in: std_logic_vector(15-skipbits downto 0);
	      PWM_out: out std_logic);
end entity PWMOUT;

architecture RTL of PWMOUT is
	signal pwm_out_unlatched,pwm_out_latched:std_logic; 
	signal value_latched: std_logic_vector (15-skipbits downto 0);
	
begin

	pwm_out_unlatched <= '1' when value_latched>clock_in else '0';
	PWM_out <= pwm_out_latched;

	process(CLK_in,RESET_in)
		begin
		
				if RESET_in='0' then
					value_latched <= (others=>'0');
                    pwm_out_latched <= '0';
				elsif rising_edge(CLK_in) then
					if (zero_in='1') then
						value_latched <= value_in;
					end if;
					pwm_out_latched <= pwm_out_unlatched;
				end if;
	 	    	
	 	end process;
end architecture RTL;
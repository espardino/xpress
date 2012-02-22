library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity prescaled_clock is
	port (CLK_in: in std_logic;
	      clock_out: out std_logic_vector (15 downto 0);
	      zero_out: out std_logic;
	      nRESET_in: in std_logic;
		  prescaler_val: in std_logic_vector(3 downto 0));
end entity prescaled_clock;

architecture RTL of prescaled_clock is

	signal clock: std_logic_vector (15 downto 0);
	signal preclk: std_logic_vector (3 downto 0);
	signal clk_en: std_logic;
	
begin

	zero_out <='1' when clock = x"0000" else '0';

	--
	-- prescaler
	--
	process (CLK_in, nRESET_in, preclk)
		variable next_preclk: std_logic_vector(3 downto 0);
		begin
				next_preclk:=std_logic_vector( unsigned(preclk) + 1 );
				if (nRESET_in='0') then
		            preclk <= (others=>'0');    
		        elsif (rising_edge(CLK_in)) then
		        	if (next_preclk>prescaler_val) then
		        		clk_en<='1';
		            	preclk <=  (others=>'0');
		            else
		            	clk_en<='0';
		            	preclk <= next_preclk;
		            
		            end if;
		        end if;
		end process;

	--
	-- clock
	--
	process (CLK_in,nRESET_in,clk_en)
	        begin
		        if (nRESET_in='0') then
		            clock <= (others=>'0');    
		        elsif (clk_en='1' and rising_edge(CLK_in)) then
		            clock <= std_logic_vector( unsigned(clock) + 1 ) ;
		        end if;
		    end process;
	clock_out <= clock;
end architecture RTL;
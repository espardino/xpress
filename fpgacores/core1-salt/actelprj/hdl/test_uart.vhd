
library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use work.txt_util.all;
Use STD.textio.all;


entity test_uart is 
end test_uart;

architecture Behavioral of test_uart is



	component xpress_uart is
	port(
		nRESET_in	    : in std_logic;
		CLK_in		    : in std_logic;
		
		CLK_PRESCALER_in : in std_logic_vector(15 downto 0);
		
		UART_STATUS_out : out std_logic_vector(15 downto 0);
		
		TX_DATA_in	    : in std_logic_vector (7 downto 0);
		LD_TX_in	    : in std_logic;
		
		RX_DATA_out		: out std_logic_vector(7 downto 0);
		CLR_RX_DATA_in	: in std_logic;
		
		RXD_in			: in std_logic;
		TXD_out			: out std_logic
		
		);
	end component;
	
	
	signal TEST_Clk    : std_logic := '0';
	signal TEST_MRST   : std_logic := '0';
	signal tx_data	   : std_logic_vector (7 downto 0);
	signal rx_data	   : std_logic_vector (7 downto 0);
	signal status : std_logic_vector(15 downto 0);
	signal ld_tx_in    : std_logic := '0';
	signal clr_data    : std_logic := '0';
	signal rxd 		   : std_logic := '1';
	signal txd		   : std_logic;
begin
	
	
	UART  :  xpress_uart port map (
			        CLK_in => TEST_Clk,
					nRESET_in => TEST_MRST,
					CLK_PRESCALER_in => "0000000110000111",
					UART_STATUS_out => status,
    	    		TX_DATA_in => tx_data,
    	    		RX_DATA_out => rx_data,
    	    		LD_TX_in => ld_tx_in,
    	    		CLR_RX_DATA_in => clr_data,
    	    		RXD_in => txd,
    	    		TXD_out => txd );
    	    		
        
         	
    
	TEST_Clk  <= NOT TEST_Clk after 11111 ps; -- 45mhz 

	-- Test reset
	TEST_MRST <= '0', '0' after 5 ns, '1' after 80 ns;
	
	tx_data <= "10101100";
	ld_tx_in <= '0', '1' after 120 ns, '0' after 140 ns;

    -- when rx_data ready tx_data must be == to rx_data

end Behavioral;
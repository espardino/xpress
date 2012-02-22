   
-----------------------------------------------------------------------------------
-- Author: Miguel Angel Ajo <miguelangel@nbee.es>
-- 
-- Create Date:    04/10/2011
-- Design Name:    Basic Core for Espardino Xpress
-- Module Name:    
-- Project Name: 
-- Target Devices: 
-- Tool versions: 
-- Description: 
--
-- Dependencies: 
--
-- Revision: 
-- Revision 0.01 - File Created
-- Additional Comments: 
--
----------------------------------------------------------------------------------


library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use work.all;
use work.xpress.all;


entity espardino_xpress_core0 is

    Port (   
    
      ADDR_in   : in std_logic_vector(5 downto 0); -- 81,80,79,78,77,76
      DATA_io   : inout std_logic_vector(15 downto 0); -- 100, 99, 98, 97, 96, 95, 94, 93, 92, 91, 90, 86, 85, 84, 83, 82
      nOE_in    : in std_logic; -- 73
      nWE_in    : in std_logic; -- 72
      nCS_in    : in std_logic_vector(1 downto 0); -- 70
      nRESET_in : in std_logic; -- 69
      CLK_in    : in std_logic; -- 65
      IRQ_out   : inout std_logic;  -- 62, inout to do open-collector

      F27,F36,F39,F44,F45,F46,F49,F51,F52,F53,F54,F55,F56,F57,  -- general purpose IOs
      F58,F59,F60,F61,F62,F63,F64,F65,F66,F67,F68,F69,F70,F71,
      F72,F73,F74,F75,F77,F83,F84,F85,F86,F87,F92,F93,F94,F95 : inout std_logic 

         ); 
end espardino_xpress_core0;

architecture behaviour of espardino_xpress_core0 is

  
	  signal registers : mem;
      signal memory_map: mem;
	  
      signal nWE,nRESET: std_logic;


      signal clock:std_logic_vector(15 downto 0);
      signal zero_clock: std_logic;
      
      signal pwm_out: std_logic_vector(9 downto 0);

      component CLKINT
        port (A : in std_logic;
            Y : out std_logic);
        end component;
	  

begin

	    u_WE_clock: CLKINT port map(A=>nWE_in, Y=>nWE);
        u_RESET: CLKINT port map(A=>nRESET_in, Y=>nRESET);
		
        --
        -- for memory access cycles see: 
        --
        -- lpc3130_3131_ds_en.pdf  pages 47-48  (section 9.2)
        --
  
        
        -- Address Latch block: on nWE or nOE falling edges
		memory_bus_ctl_inst: memory_bus_ctl port map (
											ADDR_in => ADDR_in,
											nOE_in => nOE_in,
											nWE => nWE,
											DATA_io => DATA_io,
											nCS_in => nCS_in,
											registers => registers,
											memory_map => memory_map
											);


		-- Memory Write Block: on nWE rising edge when /CS asserted
		
	    

	-- Tri-State Buffer control
    	


        --
        -- clock
        -- 
        
        prescaled_clock_inst: prescaled_clock
		port map (
		        CLK_in => CLK_in,
		        clock_out => clock,
		        zero_out=>zero_clock,
	        	nRESET_in => nRESET,
	        	prescaler_val => registers(31)(3 downto 0)
		);

        --
        -- READ Memory map wiring
        --

        memory_map(0)<=x"E000";  -- this is the core version, available on address 0
        
   	--
        -- outputs
        --	
	IRQ_out <= 'Z';
	    
 	    
        pwms: for n in 9 downto 0 generate
                    pwmout_u: PWMOUT generic map (skipbits=>0) 
                        port map (nRESET,CLK_in,clock,zero_clock,registers(4+n)(15 downto 0),pwm_out(n));
              end generate pwms;

        F77<=pwm_out(0);
        F83<=pwm_out(1);
        F84<=pwm_out(2);
        F85<=pwm_out(3);
        F86<=pwm_out(4);
        F87<=pwm_out(5);
        F92<=pwm_out(6);
        F93<=pwm_out(7);
        F94<=pwm_out(8);
        F95<=pwm_out(9);
        
        gpios0: GPIOPORT port map(PINS_io(15)=>F27,PINS_io(14)=>F36,PINS_io(13)=>F39,PINS_io(12)=>F44,
                                  PINS_io(11)=>F45,PINS_io(10)=>F46,PINS_io(9)=>F49,PINS_io(8)=>F51,
                                  PINS_io(7)=>F52, PINS_io(6)=>F53, PINS_io(5)=>F54,PINS_io(4)=>F55, 
                                  PINS_io(3)=>F56, PINS_io(2)=>F57,PINS_io(1)=>F58, PINS_io(0)=>F59,

                    			  value_in=>registers(1),
                    			  tris_in =>registers(2),
                    			  value_out=>memory_map(1));
       
 	gpios1: GPIOPORT port map(
                                  PINS_io(15)=>F60,PINS_io(14)=>F61,PINS_io(13)=>F62,PINS_io(12)=>F63,
                                  PINS_io(11)=>F64,PINS_io(10)=>F65,PINS_io(9)=>F66,PINS_io(8)=>F67,
                                  PINS_io(7)=>F68, PINS_io(6)=>F69, PINS_io(5)=>F70,PINS_io(4)=>F71, 
                                  PINS_io(3)=>F72, PINS_io(2)=>F73,PINS_io(1)=>F75, PINS_io(0)=>F75,
    
        		            	  value_in=>registers(3),
                    			  tris_in =>registers(4),
                    			  value_out=>memory_map(3));


end behaviour;
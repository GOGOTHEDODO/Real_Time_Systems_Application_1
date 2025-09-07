Henry Abshire
UCFID: 5427640
Date: 09/07/2025
Class: EEL4775

# Questions And Answers 

## Q1. Vary Priorities: Change the print task’s priority to 2 (higher than blink’s 1). With such short tasks and delays, you may not notice a big difference, but in principle the print task would preempt the blink task if it were ready. Given both tasks spend most time sleeping, the effect is minimal. In later projects with CPU-bound tasks, priority will matter more. Does anything happen to the LED if you increase the delay within the print task? What if you increase the number of characters printed? 

No, when increasing the priority of the print task or incresing the number of characters printed there was no noticable difference in the timming of the led in both visually and in printing the task timing

## Q2. Increase Load: Remove the vTaskDelay in the print task (making it a tight loop printing continuously). Be careful – this will flood the console. But it illustrates a point: if one task never yields, it can starve the other. In this case, the LED might stop blinking on schedule because the print task hogs the CPU. This is a starvation scenario, leading into Project 2. If you try this, reset it back after observing a few lines, to avoid crashing your serial output. Describe the behavior you observed.

The console is overloaded with lines, but also the LED completely goes off schedule, sometimes not blinking for seconds at a time, briefly getting back on schedule and then back to missing deadlines

## Q3. Thematic Customization: If you chose the space context, perhaps change the printed message to “Telemetry OK” or similar. In healthcare, print a pseudo heart rate. In security, print sensor status.  Assume you were a developer of one of these applications - might there be some considerations that you would want to take into consideration in how verbose (or not) you want your messages to be? Additionally, explain why this system benefits from having correct functionality at predictable times.

Yes, for my project I chose the healthcare scenario. In general, though, it creates a problem if the message being displayed takes longer for a person to read than the time period before the next message, In that case
The message loses a lot of its usefulness as it is impossible to keep pace with the system. Additionally, if your message to not verbose enough it could leave out important information that the users, in this case
health professionals, would need. Furthermore, though not shown here in our simple design, extra characters do require more time to take, process, and display. In more complicated systems, this added delay could cause issues in timing and responses. For example, in my senior design project, we designed a system with coordinated motors. After changing some of the debugging lines and altering print statements our system started to miss-time and fail because the timings were unintentionally designed with the delays from the print statements factored in. If a heart rate monitor starts to drift due to a update in a change in wording, doctors could be getting wrong information and make a decision that could kill someone

For a heart rate monitor, its important that the system provides correcting information at predictable times as it allows the doctors to respond to issues in real time. They get almost immediate feedback if a treatment is working or making it worse, and can respond accordingly. 

## Real-Time Concept Check:

## Q4. Identify/Verify the period of each task; you can try to do this via the simulator, or perhaps by printing data to the console, or connect the outputs to the logic analyzer.
###    a. Describe how you measure the periods: 
at the beginning of the for loop I use the same formula as printing the time to store the time in a variable, then on the next loop I subtract the current time with the stored previous time and print the period, the previous time is then updated with current time
###    b. LED blink task period: 
500ms (two 250ms delays)
###    c. Print task period:
10000ms or 10s

### Because we used vTaskDelay, these periods are maintained fairly accurately. In a hard real-time requirement, missing a period (e.g., LED not toggling on time) might be a system failure.

## Q5. Did our system tasks meet the timing requirements?
yes

### How do you know?
Because the tasks themselves are easily handled and the time between tasks are determined by task delay, which ensure very consistent time periods. Any slight hold up would happen on scale far below ms. 

### How did you verify it?
I calculated the time period and printed it to the terminal and then compared the calculated time period with the requirements and confirmed they were within what was required
## Q6. If the LED task had been written in a single-loop with the print (see baseline super-loop code), you might have seen the LED timing disturbed by printing (especially if printing took variable time).

### Did you try running the code?
yes
### Can you cause the LED to miss it's timing requirements?
easily
### If yes, how?
put enough stuff in the long print function that takes longer than 250ms to complete. Because we are not using tasks, the long print function will never yield and let the LED blink until it is fully finished. I accomplished this by printing "HI", 100,000,000 times. Preventing the LED from ever blinking
### If no, what did you try?
## Q7. Do you agree or disagree: By using multitasking, we were able to achieve timing determinism for the LED blink. Why or why not?
For the LED blink, yes. The program is simple enough that provided nothing catastrophic like a cosmic bit flit due a solar flare, the behavior of the system is very consistent and resilient. Thus, I would say it meets the criterion for deterministic. 



figure;
plot(Time1, ChannelA1)
hold on
plot(Time1, ChannelB1)
grid;
xlim([Time1(1) Time1(3056)])
title('AUX and Stimulation Signal vs Time')
xlabel('Time (ms)')
ylabel('Recording')
legend('Stimulation Electrode', 'AUX Port')



figure;
plot(Time, ChannelA)
hold on
plot(Time, ChannelB)
grid;
xlim([Time(1) Time(3056)])
title('AUX and Stimulation Signal vs Time')
xlabel('Time (ms)')
ylabel('Recording')
legend('Stimulation Electrode', 'AUX Port')

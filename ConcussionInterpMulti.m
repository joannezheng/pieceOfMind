clear;

i = 1;
str = '';
str = input('Results from Serial Monitor OR -1 to quit: \n', 's');
while strcmp(str,'-1') == 0
  data = strsplit(str, ' ');
  data = data';
  id(i) = data(1);
  symp(i) = sum(str2double(data(2:7)));
  orient(i) = sum(str2double(data(8:12)));
  words(i) = sum(str2double(data(13:17)));
  balance(i) = sum(str2double(data(18:19)));
  i = i+1;
  str = input('Finished string from Serial Monitor: \n', 's');
end

x = categorical({'Symptoms', 'Orientation', 'Words', 'Balance'});
y = [symp; orient; words; balance];

figure(1); clf
bar(x,y,0.5)
title(['User ID ',id{1}])
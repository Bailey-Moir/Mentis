void addition(number a, number b) {
    number sum = 0;
    number a = 1;
    number b = 30;
    number c = 100;

    if (a <= b || b <= c) print("In range");

    for (number i = 0; i < Math.max(a,b).digit_count(); i++) {
        sum+=a.nth_digit(i)+b.nth_digit(i);
    }
    return sum;
}
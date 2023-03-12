void print_tb();
void foo();
void bar();
int x = 0;
int main() {
    bar();
}
void foo() {
    if (x >= 6) {
        print_tb();
        return;
    }
    ++x;
    if (x >= 4) {
        foo();
        return;
    }
    bar();
}
void bar() {
    foo();
}

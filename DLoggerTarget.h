struct DLoggerTarget {
    virtual ~DLoggerTarget() {}

    virtual void Write(Level level, const std::string& message) = 0;
    virtual void Go(int a, double b, char c) = 0;
};

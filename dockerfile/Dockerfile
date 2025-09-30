# Start from a lightweight base image
FROM alpine:3.20

# Install a minimal web server
RUN apk add --no-cache busybox-extras

# Create a demo HTML page
RUN mkdir -p /www && \
  echo '<!DOCTYPE html><html><head><title>Demo</title></head><body><h1>Hello from Demo Container!</h1></body></html>' > /www/index.html

# Expose port 8080
EXPOSE 8080

# Run busybox httpd server
CMD ["busybox-extras", "httpd", "-f", "-v", "-p", "8080", "-h", "/www"]

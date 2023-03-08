import tsconfigPaths from "vite-tsconfig-paths";
import { configDefaults, defineConfig } from "vitest/config";

export default defineConfig({
  plugins: [tsconfigPaths()],
  test: {
    coverage: {
      reporter: ["text", "json", "html", "cobertura"],
      include: ["src"],
    },
    deps: { interopDefault: true },
    include: ["./test/**/*.ts"],
    exclude: [...configDefaults.exclude, "test/test-helpers.ts"],
  },
});
